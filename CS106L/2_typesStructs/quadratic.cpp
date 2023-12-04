#include <string>
#include <iostream>
#include <cmath> //gives us pow and sqrt!

using std::string; using std::cout;
using std::cin; using std::pow;
using std::sqrt; using std::endl;
using std::pair; using std::make_pair;

//want: a function named quadratic that will take in 3 doubles and return
//a combination of: does a solution exist, and if so, what is it?
	//get radical, test if negative, return indicating no roots
	// radical = b^2 - 4ac
	
	//otherwise get roots and return
	// root1 = (-b + sqrt(radical)) divided by 2a
	// root2 = (-b - sqrt(radical)) divided by 2a
pair<bool,pair<int,int>> quadratic(double a, double b, double c)
{
	double radical = b * b - 4 * a * c;
	if(radical < 0)return make_pair(false,make_pair(0,0));
	double root1 = (-b + sqrt(radical)) / 2.0 / a;
	double root2 = (-b - sqrt(radical)) / 2.0 / a;
	return make_pair(true, make_pair(root1, root2));
}

int main() {
	//get 3 doubles (ax^2 + bx + c)
	double a, b, c;
	cout << "Give me 3 coefficients: " << endl;
	
	//This line gets 3 numbers from user input and stores them in a, b and c 
	//we will learn more about cin on Thursday
	cin >> a >> b >> c;

	//some call to quadratic function!
	auto [exist, root] = quadratic(a, b, c);
	if(exist)cout<<"root1:"<<root.first<<" root2:"<<root.second<<endl;
	else cout<<"No roots!"<<endl;
	//get roots if they exist

	//print accordingly
	return 0;
}

// Test: x^2 + 5x + 6 = 0, roots = -3, -2

// To run: first compile code --> make quadratic, 
// then run the compiled code --> ./quadratic