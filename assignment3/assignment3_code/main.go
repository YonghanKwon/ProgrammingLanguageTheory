package main

import (
	. "calculator"
	. "calculator/num_extend"
	. "calculator/num_init"
	"fmt"
)

func main() {

	var calc Calculator
	calc.New()
	fmt.Printf("Turn on the Calculator\n%s\n", calc.GetCurrentValue())

	calc.Enter(NewInt(5))
	fmt.Printf("Enter %s\n", calc.GetCurrentValue())
	calc.Enter(NewFloat(7.6))
	fmt.Printf("Enter %s\n", calc.GetCurrentValue())
	calc.Enter(NewRational(8, 3))
	fmt.Printf("Enter %s\n", calc.GetCurrentValue())
	calc.Enter(NewRational(5, 7))
	fmt.Printf("Enter %s\n", calc.GetCurrentValue())
	calc.Operation("Mul")
	fmt.Printf("Mul\n")
	fmt.Printf("result %s\n", calc.GetCurrentValue())
	calc.Operation("Add")
	fmt.Printf("Add\n")
	fmt.Printf("result %s\n", calc.GetCurrentValue())
	calc.Operation("Div")
	fmt.Printf("Div\n")
	fmt.Printf("result %s\n", calc.GetCurrentValue())
	calc.Enter(NewComplex(NewRational(5, 9), NewInt(8)))
	fmt.Printf("Enter %s\n", calc.GetCurrentValue())
	calc.Operation("Sub")
	fmt.Printf("Sub\n")
	fmt.Printf("result %s\n", calc.GetCurrentValue())

	calc.Clear()
	fmt.Printf("Clear\n%s\n", calc.GetCurrentValue())
	calc.Enter(NewInt(5))
	fmt.Printf("Enter %s\n", calc.GetCurrentValue())
	calc.Enter(NewRational(8, 7))
	fmt.Printf("Enter %s\n", calc.GetCurrentValue())
	calc.Operation("Mul")
	fmt.Printf("Mul\n")
	fmt.Printf("result %s\n", calc.GetCurrentValue())
	calc.Enter(NewFloat(5.7))
	fmt.Printf("Enter %s\n", calc.GetCurrentValue())

	calc.Clear() //중간에 초기화도 가능
	fmt.Printf("Clear\n%s\n", calc.GetCurrentValue())
	calc.Enter(NewComplex(NewInt(6), NewFloat(7.6)))
	fmt.Printf("Enter\n%s\n", calc.GetCurrentValue())
	calc.Enter(NewComplex(NewInt(7), NewRational(7, 4)))
	fmt.Printf("Enter\n%s\n", calc.GetCurrentValue())
	calc.Enter(NewComplex(NewRational(8, 3), NewInt(6)))
	fmt.Printf("Enter\n%s\n", calc.GetCurrentValue())
	calc.Operation("Mul")
	fmt.Printf("Mul\n")
	fmt.Printf("result %s\n", calc.GetCurrentValue())
	calc.Operation("Div")
	fmt.Printf("Div\n")
	fmt.Printf("result %s\n", calc.GetCurrentValue())
}
