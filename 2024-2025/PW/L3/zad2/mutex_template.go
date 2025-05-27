package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

const (
	NrOfProcesses = 15
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

var maxTicket int = 0
var mu sync.Mutex
var choosing [NrOfProcesses]bool
var number [NrOfProcesses]int

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

func updateTicketMaximum(value int) {
	mu.Lock()
	defer mu.Unlock()
	if value > maxTicket {
		maxTicket = value
	}
}

func getTicketMaximum() int {
	mu.Lock()
	defer mu.Unlock()
	return maxTicket
}

func maxNumber() int {
	max := 0
	for _, n := range number {
		if n > max {
			max = n
		}
	}
	return max
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
	fmt.Print("MAX_TICKET=", getTicketMaximum(), ";\n")
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

		// ENTRY_PROTOCOL
		storeTrace(EntryProtocol)

		// Ticket algorithm entry protocol
		choosing[id] = true
		number[id] = maxNumber() + 1
		updateTicketMaximum(number[id])
		choosing[id] = false

		for j := 0; j < NrOfProcesses; j++ {
			if j == id {
				continue
			}
			// Wait if other process is choosing number
			for choosing[j] {
				time.Sleep(1 * time.Millisecond)
			}
			// Wait if other process has smaller ticket or same ticket but smaller id
			for number[j] != 0 && (number[j] < number[id] || (number[j] == number[id] && j < id)) {
				time.Sleep(1 * time.Millisecond)
			}
		}

		// CRITICAL_SECTION
		storeTrace(CriticalSection)
		time.Sleep(MinDelay + time.Duration(r.Int63n(int64(MaxDelay-MinDelay))))

		// EXIT_PROTOCOL
		storeTrace(ExitProtocol)
		number[id] = 0

		// Back to Local Section
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
		go process(i, time.Now().UnixNano()+int64(i), symbol, startTime, reports, &wg)
		symbol++
	}

	wg.Wait()
}
