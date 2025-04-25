package main

import (
    "fmt"
    "math/rand"
    "sync"
    "time"

    "zad5/randomseeds"
)

const (
    nrOfTravelers = 15

    minSteps = 10
    maxSteps = 100

    minDelay = 10 * time.Millisecond
    maxDelay = 50 * time.Millisecond

    boardWidth  = 15
    boardHeight = 15
)

var startTime time.Time
var board [boardWidth][boardHeight]chan struct{}

type PositionType struct {
    X int
    Y int
}

type TraceType struct {
    TimeStamp time.Duration
    ID        int
    Position  PositionType
    Symbol    rune
}

type TracesSequenceType struct {
    Last       int
    TraceArray []TraceType
}

type TravelerType struct {
    ID           int
    Symbol       rune
    Position     PositionType
    PrevPosition PositionType
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
    fmt.Printf("%f %d %d %d %c\n", trace.TimeStamp.Seconds(), trace.ID, trace.Position.X, trace.Position.Y, trace.Symbol)
}

func printTraces(traces TracesSequenceType) {
    for i := 0; i < traces.Last; i++ {
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
    startWg    *sync.WaitGroup
}

type TravelerInitData struct {
    ID     int
    Seed   int
    Symbol rune
}

func NewTravelerTask(reportChan chan TracesSequenceType, wg *sync.WaitGroup, startWg *sync.WaitGroup) *TravelerTask {
    task := &TravelerTask{
        initChan:   make(chan TravelerInitData),
        startChan:  make(chan bool),
        reportChan: reportChan,
        wg:         wg,
        startWg:    startWg,
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
    const toLower = 'a' - 'A'

    r := rand.New(rand.NewSource(int64(initData.Seed)))

    traveler := TravelerType{
        ID:     initData.ID,
        Symbol: initData.Symbol,
        Position: PositionType{
            X: initData.ID,
            Y: initData.ID,
        },
        PrevPosition: PositionType{0, 0},
    }

    nrOfSteps := minSteps + r.Intn(maxSteps-minSteps+1)
    traces := TracesSequenceType{
        Last:       0,
        TraceArray: make([]TraceType, maxSteps+1),
    }
    
    n := r.Intn(2) + (initData.ID%2)*2

    storeTrace := func(timestamp time.Duration) {
        traces.TraceArray[traces.Last] = TraceType{
            TimeStamp: timestamp,
            ID:        traveler.ID,
            Position:  traveler.Position,
            Symbol:    traveler.Symbol,
        }
        traces.Last++
    }

    makeStep := func() {
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
    t.startWg.Done()
    t.startWg.Wait()

    select {
    case <-board[traveler.Position.X][traveler.Position.Y]:
        storeTrace(time.Since(startTime))
    case <-time.After(nrOfTravelers * maxDelay):
        nrOfSteps = 0
    }

    step := 0
    for step < nrOfSteps {
        delay := minDelay + time.Duration(r.Intn(int(maxDelay-minDelay)+1))
        time.Sleep(delay)

        traveler.PrevPosition.X = traveler.Position.X
        traveler.PrevPosition.Y = traveler.Position.Y
        makeStep()

        select {
        case <-board[traveler.Position.X][traveler.Position.Y]:
            storeTrace(time.Since(startTime))
            board[traveler.PrevPosition.X][traveler.PrevPosition.Y] <- struct{}{}
        case <-time.After(nrOfTravelers * maxDelay):
            traveler.Symbol = traveler.Symbol + toLower
            traveler.Position.X = traveler.PrevPosition.X
            traveler.Position.Y = traveler.PrevPosition.Y
            storeTrace(time.Since(startTime))
            step = nrOfSteps
        }
        step++
    }

    t.reportChan <- traces
}

func main() {
    startTime = time.Now()

    fmt.Printf("-1 %d %d %d\n", nrOfTravelers, boardWidth, boardHeight)

    for i := 0; i < boardWidth; i++ {
        for j := 0; j < boardHeight; j++ {
            board[i][j] = make(chan struct{}, 1)
            board[i][j] <- struct{}{}
        }
    }

    reportChan := make(chan TracesSequenceType, nrOfTravelers)

    var wg sync.WaitGroup
    var printerWg sync.WaitGroup
    var startWg sync.WaitGroup

    seeds := randomseeds.MakeSeeds(nrOfTravelers)

    printerWg.Add(1)
    go printer(reportChan, &printerWg)

    travelTasks := make([]*TravelerTask, nrOfTravelers)
    symbol := 'A'
    wg.Add(nrOfTravelers)
    startWg.Add(nrOfTravelers)

    for i := 0; i < nrOfTravelers; i++ {
        travelTasks[i] = NewTravelerTask(reportChan, &wg, &startWg)
        travelTasks[i].Init(i, seeds[i], symbol)
        symbol++
    }

    for i := 0; i < nrOfTravelers; i++ {
        travelTasks[i].Start()
    }

    wg.Wait()
    printerWg.Wait()
}
