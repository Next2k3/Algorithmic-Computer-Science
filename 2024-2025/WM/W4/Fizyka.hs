module Fizyka(Point,Vector,Time,move,translate,moveInGF) where

type Point = (Double,Double)
type Vector = (Double,Double)
type Time = Double

constG = 9.80655

generalMove :: Point -> Vector -> Time -> Double -> Point 
generalMove (x,y) (vx,vy) t acc = (x+vx*t, y + vy*t + acc*t*t/2)

move :: Point -> Vector -> Time -> Point
move p v t = generalMove p v t 0

translate :: Point -> Vector -> Point
translate p v = generalMove p v 1 0

moveInGF :: Point -> Vector -> Time -> Point
moveInGF p v t = generalMove p v t (-constG)

