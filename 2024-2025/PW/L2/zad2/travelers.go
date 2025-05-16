package main

import (
	"fmt"
	"math/rand"
	"time"
)

const (
	NrOfTravelers     = 20
	NrOfWildTravelers = 10
	MinSteps          = 10
	MaxSteps          = 100
	MinDelay          = 10 * time.Millisecond
	MaxDelay          = 50 * time.Millisecond
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
	p.TraceChannel = make(chan []Trace, NrOfTravelers)
	p.Done = make(chan bool)

	go func() {
		for i := 0; i < NrOfTravelers+NrOfWildTravelers; i++ {
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
	Success Response = iota
	Fail
	Deadlock
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

// Struktura dla zapytań o przemieszczenie podróżników
type RelocateRequest struct {
	Position Position
	Status   Response
	Ack      chan struct{} // Potwierdzenie zakończenia operacji
}

type Wild struct {
	Traveler
	RelocateChannel chan RelocateRequest

	timeAppear    time.Duration
	timeDisappear time.Duration
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
	waiting  []EnterRequest
}

func (n *Node) Init(position Position) {
	n.EnterChannel = make(chan EnterRequest)
	n.LeaveChannel = make(chan bool)

	n.position = position
	n.traveler = nil

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
					Request.ResponseChannel <- Success
				} else if _, ok := n.traveler.(*Legal); ok {
					// Jeśli jest już tam podróżnik, nie wchodzi nowy
					Request.ResponseChannel <- Fail
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

							request := EnterRequest{n.traveler, make(chan Response)}
							Board[candidatePosition.X][candidatePosition.Y].EnterChannel <- request
							nodeResponse = <-request.ResponseChannel

							if nodeResponse != Fail {
								newPosition = candidatePosition
								break
							}
						}

						// Jeśli udało się znaleźć wolne miejsce, przenosimy dzikiego lokatora
						if nodeResponse != Fail {
							ack := make(chan struct{})
							wild.RelocateChannel <- RelocateRequest{newPosition, Success, ack}
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
	// Próba umiejscowienia podróżnika na planszy
	for t.response == Fail {
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
			if t.response == Deadlock {
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

					request := EnterRequest{t, make(chan Response, 1)}
					Board[newPosition.X][newPosition.Y].EnterChannel <- request

					select {
					case t.response = <-request.ResponseChannel:
						// Jeśli odpowiedź to Success, podróżnik idzie na nowe pole
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

			// Obsługuje odpowiedź
			switch t.response {
			case Success:
				// Jeśli udało się przejść, zwalniamy pole
				Board[t.Position.X][t.Position.Y].LeaveChannel <- true
				t.Position = newPosition

			case Deadlock:
				t.Symbol = rune(int(t.Symbol) + 32)
			}

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

		// Próba umiejscowienia dzikiego lokatora na planszy
		t.response = Fail
		for t.response == Fail {
			t.Position = Position{
				X: rand.Intn(BoardWidth),
				Y: rand.Intn(BoardHeight),
			}

			request := EnterRequest{t, make(chan Response)}
			Board[t.Position.X][t.Position.Y].EnterChannel <- request
			t.response = <-request.ResponseChannel
		}

		t.timeStamp = time.Since(StartTime)
		t.Store_Trace()

		for true {
			if time.Since(StartTime) > t.timeDisappear {
				break
			}

			select {
			case Request := <-t.RelocateChannel:
				t.response = Request.Status
				t.Position = Request.Position
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

func main() {
	var travelers [NrOfTravelers + NrOfWildTravelers]GeneralTraveler

	fmt.Printf(
		"-1 %d %d %d\n",
		NrOfTravelers+NrOfWildTravelers,
		BoardWidth,
		BoardHeight,
	)

	printer.Start()

	for i := 0; i < BoardWidth; i++ {
		for j := 0; j < BoardHeight; j++ {
			Board[i][j].Init(Position{i, j})
		}
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
