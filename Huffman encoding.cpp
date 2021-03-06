// Huffman encoding.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "HuffmanAlgorithm.h"

int main()
{
	ifstream inputText("example.txt");
	stringstream buffer;
	buffer << inputText.rdbuf();
	string text = buffer.str();
	Node<pair<char, int>>* tree = huffmanAlgorithm(text);

	//Decoding a sample substring of our text
	
	string sampleString = "0110000110110010011001100"; // BIG
	cout << "\n Having the huffman tree, we can just pick a valid encoded string of bits and decode it. Example:\n" << sampleString << " - ";
	int idx = -1;
	while (idx < (int)(sampleString.length() - 1)) {
		decodeLetter(tree, idx, sampleString);
	}
	cout << endl;
	return 0;
}
