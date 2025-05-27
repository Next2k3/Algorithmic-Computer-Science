package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

const (
	NrOfProcesses = 2
	MinSteps      = 50
	MaxSteps      = 100
	MinDelay      = 10 * time.Millisecond
	MaxDelay      = 50 * time.Millisecond
)

type ProcessState int

const (
	LocalSection ProcessState = iota
	EntryProtocol
	CriticalSection
	ExitProtocol
)

var processStates = []string{
	"Local_Section",
	"Entry_Protocol",
	"Critical_Section",
	"Exit_Protocol",
}

var flag [2]bool
var turn int = 0

type Position struct {
	X, Y int
}

type Trace struct {
	TimeStamp time.Duration
	Id        int
	Position  Position
	Symbol    rune
}

type TraceReport struct {
	Traces []Trace
}

func printTrace(t Trace) {
	fmt.Printf("%d %d %d %d %c\n", t.TimeStamp.Nanoseconds(), t.Id, t.Position.X, t.Position.Y, t.Symbol)
}

func printTraces(traces []Trace) {
	for _, t := range traces {
		printTrace(t)
	}
}

func printer(wg *sync.WaitGroup, reports <-chan TraceReport) {
	defer wg.Done()

	for i := 0; i < NrOfProcesses; i++ {
		report := <-reports
		printTraces(report.Traces)
	}

	fmt.Printf("-1 %d %d %d ", NrOfProcesses, NrOfProcesses, len(processStates))
	for _, s := range processStates {
		fmt.Print(s + ";")
	}
	fmt.Println("EXTRA_LABEL;")
}

func entryProtocolDekker(id int, flag *[2]bool, turn *int) {
	other := 1 - id
	flag[id] = true

	for flag[other]{
		if *turn == other {
			flag[id] = false
			time.Sleep(1 * time.Millisecond)
			flag[id] = true
		}
	}
}

func exitProtocolDekker(id int, flag *[2]bool, turn *int) {
	*turn = 1 - id
	flag[id] = false
}

func process(id int, seed int64, symbol rune, startTime time.Time, reports chan<- TraceReport, wg *sync.WaitGroup) {
	defer wg.Done()

	r := rand.New(rand.NewSource(seed))
	var traces []Trace

	storeTrace := func(state ProcessState) {
		trace := Trace{
			TimeStamp: time.Since(startTime),
			Id:        id,
			Position:  Position{X: id, Y: int(state)},
			Symbol:    symbol,
		}
		traces = append(traces, trace)
	}

	nrOfSteps := MinSteps + r.Intn(MaxSteps-MinSteps+1)
	storeTrace(LocalSection)

	for step := 0; step < nrOfSteps; step++ {
		time.Sleep(MinDelay + time.Duration(r.Int63n(int64(MaxDelay-MinDelay))))

		storeTrace(EntryProtocol)

		// ENTRY_PROTOCOL
		entryProtocolDekker(id, &flag, &turn)

		storeTrace(CriticalSection)
		time.Sleep(MinDelay + time.Duration(r.Int63n(int64(MaxDelay-MinDelay))))

		storeTrace(ExitProtocol)

		// EXIT_PROTOCOL
		exitProtocolDekker(id, &flag, &turn)

		storeTrace(LocalSection)
	}

	reports <- TraceReport{Traces: traces}
}

func main() {
	startTime := time.Now()
	reports := make(chan TraceReport, NrOfProcesses)
	var wg sync.WaitGroup

	wg.Add(1)
	go printer(&wg, reports)

	wg.Add(NrOfProcesses)
	symbol := 'A'

	for i := 0; i < NrOfProcesses; i++ {
		go process(i, rand.Int63(), symbol, startTime, reports, &wg)
		symbol++
	}

	wg.Wait()
}
