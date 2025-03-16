package main

import "fmt"

func main() {
	messanges := make(chan string, 2)

	messanges <- "buffered"
	messanges <- "channel"

	fmt.Println(<-messanges)
	fmt.Println(<-messanges)

}
