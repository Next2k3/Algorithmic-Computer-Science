package main

import (
	"fmt"
	"math"
	"math/rand"
	"sync"
	"time"

	"zad1/randomseeds"
)

const (
	nrOfTravelers = 15

	minSteps = 10
	maxSteps = 100

	minDelay = 10 * time.Millisecond
	maxDelay = 50 * time.Millisecond

	boardWidth  = 5
	boardHeight = 5
)

var startTime time.Time

type PositionType struct {
	X int
	Y int
}

type TraceType struct {
	TimeStamp float64
	ID        int
	Position  PositionType
	Symbol    rune
}

type TracesSequenceType struct {
	Last       int
	TraceArray []TraceType
}

type TravelerType struct {
	ID       int
	Symbol   rune
	Position PositionType
}

func moveDown(position *PositionType) {
	position.Y = (position.Y + 1) % boardHeight
}

func moveUp(position *PositionType) {
	position.Y = (position.Y + boardHeight - 1) % boardHeight
}

func moveRight(position *PositionType) {
	position.X = (position.X + 1) % boardWidth
}

func moveLeft(position *PositionType) {
	position.X = (position.X + boardWidth - 1) % boardWidth
}

func printTrace(trace TraceType) {
	fmt.Printf("%f %d %d %d %c\n", trace.TimeStamp, trace.ID, trace.Position.X, trace.Position.Y, trace.Symbol)
}

func printTraces(traces TracesSequenceType) {
	for i := 0; i <= traces.Last; i++ {
		printTrace(traces.TraceArray[i])
	}
}

func printer(reportChan chan TracesSequenceType, wg *sync.WaitGroup) {
	defer wg.Done()

	for i := 0; i < nrOfTravelers; i++ {
		traces := <-reportChan
		printTraces(traces)
	}
}

type TravelerTask struct {
	initChan   chan TravelerInitData
	startChan  chan bool
	reportChan chan TracesSequenceType
	wg         *sync.WaitGroup
}

type TravelerInitData struct {
	ID     int
	Seed   int
	Symbol rune
}

func NewTravelerTask(reportChan chan TracesSequenceType, wg *sync.WaitGroup) *TravelerTask {
	task := &TravelerTask{
		initChan:   make(chan TravelerInitData),
		startChan:  make(chan bool),
		reportChan: reportChan,
		wg:         wg,
	}

	go task.run()
	return task
}

func (t *TravelerTask) Init(id int, seed int, symbol rune) {
	t.initChan <- TravelerInitData{ID: id, Seed: seed, Symbol: symbol}
}

func (t *TravelerTask) Start() {
	t.startChan <- true
}

func (t *TravelerTask) run() {
	defer t.wg.Done()

	initData := <-t.initChan

	r := rand.New(rand.NewSource(int64(initData.Seed)))

	traveler := TravelerType{
		ID:     initData.ID,
		Symbol: initData.Symbol,
		Position: PositionType{
			X: int(math.Floor(float64(boardWidth) * r.Float64())),
			Y: int(math.Floor(float64(boardHeight) * r.Float64())),
		},
	}

	traces := TracesSequenceType{
		Last:       -1,
		TraceArray: make([]TraceType, maxSteps+1),
	}

	storeTrace := func() {
		timeStamp := time.Since(startTime).Seconds()
		traces.Last++
		traces.TraceArray[traces.Last] = TraceType{
			TimeStamp: timeStamp,
			ID:        traveler.ID,
			Position:  traveler.Position,
			Symbol:    traveler.Symbol,
		}
	}

	storeTrace()

	nrOfSteps := minSteps + int(float64(maxSteps-minSteps)*r.Float64())

	makeStep := func() {
		n := int(math.Floor(4.0 * r.Float64()))
		switch n {
		case 0:
			moveUp(&traveler.Position)
		case 1:
			moveDown(&traveler.Position)
		case 2:
			moveLeft(&traveler.Position)
		case 3:
			moveRight(&traveler.Position)
		default:
			fmt.Printf(" ?????????????? %d\n", n)
		}
	}

	<-t.startChan

	for step := 0; step <= nrOfSteps; step++ {
		delay := minDelay + time.Duration(r.Float64()*float64(maxDelay-minDelay))
		time.Sleep(delay)

		makeStep()
		storeTrace()
	}

	t.reportChan <- traces
}

func main() {
	startTime = time.Now()

	fmt.Printf("-1 %d %d %d\n", nrOfTravelers, boardWidth, boardHeight)

	reportChan := make(chan TracesSequenceType, nrOfTravelers)

	var wg sync.WaitGroup
	var printerWg sync.WaitGroup

	seeds := randomseeds.MakeSeeds(nrOfTravelers)

	printerWg.Add(1)
	go printer(reportChan, &printerWg)

	travelTasks := make([]*TravelerTask, nrOfTravelers)
	symbol := 'A'
	wg.Add(nrOfTravelers)

	for i := 0; i < nrOfTravelers; i++ {
		travelTasks[i] = NewTravelerTask(reportChan, &wg)
		travelTasks[i].Init(i, seeds[i], symbol)
		symbol++
	}

	for i := 0; i < nrOfTravelers; i++ {
		travelTasks[i].Start()
	}

	wg.Wait()

	printerWg.Wait()
}
