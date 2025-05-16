package main

import (
	"fmt"
	"math/rand"
	"time"
)

const (
	NrOfTravelers     = 20
	NrOfWildTravelers = 10
	NrOfTraps         = 5
	MinSteps          = 10
	MaxSteps          = 100
	MinDelay          = 10 * time.Millisecond
	MaxDelay          = 50 * time.Millisecond
	TrapDelay         = 50 * time.Millisecond
	Timeout           = 200 * time.Millisecond
	BoardWidth        = 10
	BoardHeight       = 10
)

var (
	StartTime = time.Now()
	printer   = Printer{}
	Board     = [BoardWidth][BoardHeight]Node{}
)

type Position struct {
	X, Y int
}

func Move_Down(pos *Position) {
	pos.Y = (pos.Y + 1) % BoardHeight
}

func Move_Up(pos *Position) {
	pos.Y = (pos.Y + BoardHeight - 1) % BoardHeight
}

func Move_Right(pos *Position) {
	pos.X = (pos.X + 1) % BoardWidth
}

func Move_Left(pos *Position) {
	pos.X = (pos.X + BoardWidth - 1) % BoardWidth
}

func Move_Direction(pos *Position, direction int) {
	switch direction {
	case 0:
		Move_Up(pos)
	case 1:
		Move_Down(pos)
	case 2:
		Move_Left(pos)
	case 3:
		Move_Right(pos)
	}
}

type Trace struct {
	TimeStamp time.Duration
	Id        int
	Position  Position
	Symbol    rune
}

func Print_Traces(traces []Trace) {
	for _, trace := range traces {
		fmt.Printf("%f %d %d %d %c\n",
			float64(trace.TimeStamp)/float64(time.Second),
			trace.Id,
			trace.Position.X,
			trace.Position.Y,
			trace.Symbol,
		)
	}
}

type Printer struct {
	TraceChannel chan []Trace
	Done         chan bool
}

func (p *Printer) Start() {
	p.TraceChannel = make(chan []Trace, NrOfTravelers+NrOfWildTravelers+NrOfTraps)
	p.Done = make(chan bool)

	go func() {
		for i := 0; i < NrOfTravelers+NrOfWildTravelers+NrOfTraps; i++ {
			traces := <-p.TraceChannel
			Print_Traces(traces)
		}

		p.Done <- true
	}()
}

type GeneralTraveler interface {
	Init(id int, symbol rune)
	Start()
	Store_Trace()
}

type Response int

const (
	Success    Response = iota // Udany ruch
	Fail                       // Nieudany ruch
	Deadlock                   // Deadlock
	TrapCaught                 // Złapany w pułapkę
)

type Traveler struct {
	Id        int
	Symbol    rune
	Position  Position
	traces    []Trace
	timeStamp time.Duration
	response  Response
}

type Legal struct {
	Traveler
	steps int
}

type RelocateRequest struct {
	Position Position
	Status   Response
	Ack      chan struct{}
}

type Wild struct {
	Traveler
	RelocateChannel chan RelocateRequest

	timeAppear    time.Duration
	timeDisappear time.Duration
}

type Trap struct {
	Traveler
	CaughtChannel chan GeneralTraveler
}

type EnterRequest struct {
	Traveler        GeneralTraveler
	ResponseChannel chan Response
}

type Node struct {
	EnterChannel chan EnterRequest
	LeaveChannel chan bool

	position Position
	traveler GeneralTraveler
	isTrap   bool
	waiting  []EnterRequest
}

func (n *Node) Init(position Position) {
	n.EnterChannel = make(chan EnterRequest)
	n.LeaveChannel = make(chan bool)

	n.position = position
	n.traveler = nil
	n.isTrap = false

	n.Start()
}

func (n *Node) Start() {
	go func() {
		for {
			select {
			case Request := <-n.EnterChannel:
				if n.traveler == nil {
					// Jeśli pole jest puste, podróżnik wchodzi
					n.traveler = Request.Traveler

					// Sprawdzamy czy pole jest pułapką
					if n.isTrap {
						Request.ResponseChannel <- TrapCaught
					} else {
						Request.ResponseChannel <- Success
					}
				} else if _, ok := n.traveler.(*Legal); ok {
					// Jeśli jest już tam legalny podróżnik, nie wchodzi nowy
					Request.ResponseChannel <- Fail
				} else if _, ok := n.traveler.(*Trap); ok {
					// Jeśli pole jest pułapką, podróżnik wpada w pułapkę
					Request.ResponseChannel <- TrapCaught
				} else if wild, ok := n.traveler.(*Wild); ok {
					// Jeśli jest dziki lokator
					if _, ok := Request.Traveler.(*Legal); ok {
						var candidatePosition Position
						var newPosition Position
						var nodeResponse Response
						directions := []int{0, 1, 2, 3}

						// Próba znalezienia wolnego miejsca do przeniesienia dzikiego lokatora
						for _, dir := range directions {
							candidatePosition = n.position
							Move_Direction(&candidatePosition, dir)

							// Wysyłanie zapytania do sąsiednich węzłów
							request := EnterRequest{n.traveler, make(chan Response)}
							Board[candidatePosition.X][candidatePosition.Y].EnterChannel <- request
							nodeResponse = <-request.ResponseChannel

							if nodeResponse == Success {
								newPosition = candidatePosition
								break
							} else if nodeResponse == TrapCaught {
								// Jeśli sąsiednie pole jest pułapką, dziki lokator wpada w nią
								newPosition = candidatePosition
								wild.response = TrapCaught
								break
							}
						}

						// Jeśli udało się znaleźć wolne miejsce, przenosimy dzikiego lokatora
						if nodeResponse == Success || nodeResponse == TrapCaught {
							ack := make(chan struct{})
							wild.RelocateChannel <- RelocateRequest{newPosition, wild.response, ack}
							<-ack

							n.traveler = Request.Traveler
							Request.ResponseChannel <- Success
						} else {
							Request.ResponseChannel <- Fail
						}
					} else {
						Request.ResponseChannel <- Fail
					}
				} else {
					Request.ResponseChannel <- Fail
				}
			case <-n.LeaveChannel:
				// Zwalniamy pole
				n.traveler = nil
			}
		}
	}()
}

func (n *Node) SetTrap(trap *Trap) {
	n.isTrap = true
	n.traveler = trap
}

func (t *Traveler) Store_Trace() {
	t.traces = append(t.traces, Trace{
		TimeStamp: t.timeStamp,
		Id:        t.Id,
		Position:  t.Position,
		Symbol:    t.Symbol,
	})
}

func (t *Legal) Init(id int, symbol rune) {
	t.Id = id
	t.Symbol = symbol
	t.steps = MinSteps + rand.Intn(MaxSteps-MinSteps+1)

	t.response = Fail
	for t.response == Fail && t.response != TrapCaught {
		t.Position = Position{
			X: rand.Intn(BoardWidth),
			Y: rand.Intn(BoardHeight),
		}

		request := EnterRequest{t, make(chan Response, 1)}
		Board[t.Position.X][t.Position.Y].EnterChannel <- request
		t.response = <-request.ResponseChannel
	}

	t.timeStamp = time.Since(StartTime)
	t.Store_Trace()
}

func (t *Legal) Start() {
	go func() {
		for i := 0; i < t.steps; i++ {
			if t.response == Deadlock || t.response == TrapCaught {
				break
			}

			time.Sleep(MinDelay + time.Duration(rand.Intn(int(MaxDelay-MinDelay))))

			successChannel := make(chan bool, 1)
			deadlockChannel := make(chan bool, 1)

			var newPosition Position

			go func() {
				t.response = Fail

				for t.response == Fail {
					newPosition = t.Position
					Move_Direction(&newPosition, rand.Intn(4))

					// Wysyłanie zapytania do odpowiedniego węzła
					request := EnterRequest{t, make(chan Response, 1)}
					Board[newPosition.X][newPosition.Y].EnterChannel <- request

					select {
					case t.response = <-request.ResponseChannel:
						// Jeśli odpowiedź to Success lub TrapCaught, podróżnik idzie na nowe pole
						if t.response != Fail {
							successChannel <- true
						} else {
							// Jeśli napotkaliśmy innego podróżnika, czekamy chwilę
							time.Sleep(time.Millisecond)
						}

					case <-deadlockChannel:
						// Jeśli deadlock, ustawiamy odpowiedź na Deadlock
						t.response = Deadlock
					}
				}
			}()

			select {
			case <-successChannel:
			case <-time.After(4 * MaxDelay):
				deadlockChannel <- true
			}

			switch t.response {
			case Success:
				// Jeśli udało się przejść, zwalniamy pole
				Board[t.Position.X][t.Position.Y].LeaveChannel <- true
				t.Position = newPosition

			case TrapCaught:
				// Podróżnik wpadł w pułapkę
				Board[t.Position.X][t.Position.Y].LeaveChannel <- true
				t.Position = newPosition

				// Zmiana symbolu na małą literę
				t.Symbol = rune(int(t.Symbol) + 32)
				t.timeStamp = time.Since(StartTime)
				t.Store_Trace()

				// Uśpienie na chwilę
				time.Sleep(TrapDelay)

				// Zwolnienie pola pułapki i zakończenie działania
				Board[t.Position.X][t.Position.Y].LeaveChannel <- true

				// Zapis ostatniego śladu poza planszą
				t.Position = Position{BoardWidth, BoardHeight}
				t.Symbol = '#'
				t.timeStamp = time.Since(StartTime)
				t.Store_Trace()

				printer.TraceChannel <- t.traces
				return

			case Deadlock:
				t.Symbol = rune(int(t.Symbol) + 32)
			}

			t.timeStamp = time.Since(StartTime)
			t.Store_Trace()
		}

		if t.response != TrapCaught {
			Board[t.Position.X][t.Position.Y].LeaveChannel <- true

			t.Position = Position{BoardWidth, BoardHeight}
			t.timeStamp = time.Since(StartTime)
			t.Store_Trace()
		}

		printer.TraceChannel <- t.traces
	}()
}

func (t *Wild) Init(id int, symbol rune) {
	t.RelocateChannel = make(chan RelocateRequest)
	t.Id = id
	t.Symbol = symbol
	t.timeAppear = time.Duration(rand.Intn(int(MaxDelay)))
	t.timeDisappear = t.timeAppear + time.Duration(rand.Int63n(int64(MaxDelay*MaxSteps-t.timeAppear)))
}

func (t *Wild) Start() {
	go func() {
		time.Sleep(t.timeAppear)

		t.response = Fail
		for t.response == Fail {
			t.Position = Position{
				X: rand.Intn(BoardWidth),
				Y: rand.Intn(BoardHeight),
			}

			request := EnterRequest{t, make(chan Response)}
			Board[t.Position.X][t.Position.Y].EnterChannel <- request
			t.response = <-request.ResponseChannel

			if t.response == TrapCaught {
				t.response = Fail
			}
		}

		t.timeStamp = time.Since(StartTime)
		t.Store_Trace()

		for {
			if time.Since(StartTime) > t.timeDisappear {
				break
			}

			select {
			case Request := <-t.RelocateChannel:
				// Relokacja lokatora
				t.response = Request.Status
				t.Position = Request.Position

				// Jeśli wpadł w pułapkę
				if t.response == TrapCaught {
					t.Symbol = '*'
					t.timeStamp = time.Since(StartTime)
					t.Store_Trace()

					time.Sleep(TrapDelay)

					Board[t.Position.X][t.Position.Y].LeaveChannel <- true

					t.Position = Position{BoardWidth, BoardHeight}
					t.timeStamp = time.Since(StartTime)
					t.Store_Trace()

					Request.Ack <- struct{}{}

					printer.TraceChannel <- t.traces
					return
				}

				t.timeStamp = time.Since(StartTime)
				t.Store_Trace()

				Request.Ack <- struct{}{}

			case <-time.After(t.timeDisappear - time.Since(StartTime)):
			}
		}

		// Zwolnienie planszy po zniknięciu lokatora
		Board[t.Position.X][t.Position.Y].LeaveChannel <- true
		t.Position = Position{
			X: BoardWidth,
			Y: BoardHeight,
		}
		t.timeStamp = time.Since(StartTime)
		t.Store_Trace()

		printer.TraceChannel <- t.traces
	}()
}

func (t *Trap) Init(id int, symbol rune) {
	t.Id = id
	t.Symbol = symbol
	t.CaughtChannel = make(chan GeneralTraveler)

	for {
		t.Position = Position{
			X: rand.Intn(BoardWidth),
			Y: rand.Intn(BoardHeight),
		}

		request := EnterRequest{t, make(chan Response)}
		Board[t.Position.X][t.Position.Y].EnterChannel <- request
		t.response = <-request.ResponseChannel

		if t.response == Success {
			Board[t.Position.X][t.Position.Y].SetTrap(t)
			break
		}
	}

	t.timeStamp = time.Since(StartTime)
	t.Store_Trace()
}

func (t *Trap) Start() {
	go func() {
		time.Sleep(time.Duration(MinSteps+MaxSteps) * MaxDelay * 2)

		printer.TraceChannel <- t.traces
	}()
}

func main() {
	var travelers [NrOfTravelers + NrOfWildTravelers]GeneralTraveler
	var traps [NrOfTraps]Trap

	fmt.Printf(
		"-1 %d %d %d\n",
		NrOfTravelers+NrOfWildTravelers+NrOfTraps,
		BoardWidth,
		BoardHeight,
	)

	printer.Start()

	for i := 0; i < BoardWidth; i++ {
		for j := 0; j < BoardHeight; j++ {
			Board[i][j].Init(Position{i, j})
		}
	}

	for i := 0; i < NrOfTraps; i++ {
		traps[i].Init(NrOfTravelers+NrOfWildTravelers+i, '#')
	}

	id := 0
	symbol := 'A'
	for i := 0; i < NrOfTravelers; i++ {
		travelers[id] = &Legal{}
		travelers[id].Init(id, symbol)
		id++
		symbol++
	}

	symbol = '0'
	for i := 0; i < NrOfWildTravelers; i++ {
		travelers[id] = &Wild{}
		travelers[id].Init(id, symbol)
		id++
		symbol++
	}

	for i := 0; i < NrOfTraps; i++ {
		traps[i].Start()
	}

	id = 0
	for i := 0; i < NrOfTravelers; i++ {
		travelers[id].Start()
		id++
	}

	for i := 0; i < NrOfWildTravelers; i++ {
		travelers[id].Start()
		id++
	}

	<-printer.Done
}
