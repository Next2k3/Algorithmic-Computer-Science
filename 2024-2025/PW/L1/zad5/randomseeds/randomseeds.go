package randomseeds

import (
	"math/rand"
	"time"
)

const SeedRange float64 = 1.0e6

type SeedArrayType []int

func MakeSeeds(size int) SeedArrayType {

	generator := rand.New(rand.NewSource(time.Now().UnixNano()))

	seedArray := make(SeedArrayType, size)

	for i := range seedArray {
		seedArray[i] = int(SeedRange * generator.Float64())
	}

	return seedArray
}
