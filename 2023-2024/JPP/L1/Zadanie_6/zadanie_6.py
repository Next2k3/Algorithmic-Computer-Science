from ctypes import CDLL, Structure, c_int, c_ulonglong

lib = CDLL('./libZadanie_1_iter.so')

class DiophantineSolution(Structure):
	_fields_ = [("x", c_int),("y", c_int)]

factorial = lib.factorial
factorial.argtypes = [c_int]
factorial.restype = c_ulonglong

gcd = lib.gcd
gcd.argtypes = [c_int, c_int]
gcd.restype = c_int

diophantine = lib.diophantine
diophantine.argtypes = [c_int, c_int, c_int]
diophantine.restype = DiophantineSolution

