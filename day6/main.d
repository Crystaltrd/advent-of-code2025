import std.stdio;
import std.string;
import std.container;
import std.uni;
import std.conv;
import std.range;
import std.algorithm;
import std.math;
void main() {
    File input = File("input", "r");

	long[][] matrix;
	long sum = 0;
	string[] symbols;
	while (!input.eof()) {
        string line = strip(input.readln());
		if(line.length == 0)
			continue;
		if(isNumber(line[0])){
			auto numbers = to!(long[])(line.split());
			matrix.length = numbers.length;
			foreach (i, e; numbers) {
				writeln(floor(log10(e)));
				matrix[i] ~= e;
			}			
		}
		else{
			symbols = line.split();
			foreach (i, e; symbols) {
				if(e == "+")
				sum += (matrix[i]).fold!((a,e) => a+e);
				else
				sum +=(matrix[i]).fold!((a,e) => a*e);
			}
		}
	} 
	writeln(sum);
	

}
