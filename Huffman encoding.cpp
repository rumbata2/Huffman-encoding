// Huffman encoding.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <fstream>
#include <sstream>
using namespace std;

template <typename T>
struct Node {
	T data;
	Node<T> *left, *right;

	Node(T _data, Node<T> *_left = nullptr, Node<T> *_right = nullptr) {
		data = _data;
		left = _left;
		right = _right;
	}
};

struct compare {
	bool operator()(Node<pair<char, int>>* p1, Node<pair<char, int>>* p2) {
		return p1->data.second > p2->data.second;
	}
};

Node<pair<char, int>>* makeHuffmanNode(char ch, int freq, Node<pair<char, int>> *left, Node<pair<char, int>> *right) {
	pair<char, int> newPair;
	newPair.first = ch;
	newPair.second = freq;
	Node<pair<char, int>>* node = new Node<pair<char, int>>(newPair, left, right);

	return node;
}

void traverseHuffmanTree(Node<pair<char, int>>* root, string str, unordered_map<char, string>& huffmanCodes) {
	if (root == nullptr)
		return;

	if (root->left == nullptr && root->right == nullptr) {
		huffmanCodes[root->data.first] = str;
	}

	traverseHuffmanTree(root->left, str + "0", huffmanCodes);
	traverseHuffmanTree(root->right, str + "1", huffmanCodes);
}

void decodeLetter(Node<pair<char, int>>* root, int& index, string encodedString) {
	if (root == nullptr)
		return;
	if (root->left == nullptr && root->right == nullptr) {
		cout << root->data.first;
		return;
	}
	index++;

	if (encodedString[index] == '0')
		decodeLetter(root->left, index, encodedString);
	else
		decodeLetter(root->right, index, encodedString);
}
Node<pair<char, int>>* huffmanAlgorithm(string text) {
	vector<pair<char, int>> histogram;
	for (int i = 0; i < text.length(); i++) {
		char temp = text[i];
		bool incrementFlag = false;

		for (int j = 0; j < histogram.size(); j++) {
			if (histogram[j].first == temp) {
				histogram[j].second++;
				incrementFlag = true;
				break;
			}
		}
		if (!incrementFlag) {
			std::pair<char, int> newLetter;
			newLetter.first = temp;
			newLetter.second = 1;
			histogram.push_back(newLetter);
		}
	}

	priority_queue<Node<pair<char, int>>*, vector<Node<pair<char, int>>*>, compare> pq;

	for (int i = 0; i < histogram.size(); i++) {
		pq.push(makeHuffmanNode(histogram[i].first, histogram[i].second, nullptr, nullptr));
	}

	/*while (!pq.empty()) {
	cout << pq.top()->data.first << " " << pq.top()->data.second << endl;
	pq.pop();
	}*/

	while (pq.size() > 1) {
		Node<pair<char, int>> *left = pq.top();
		pq.pop();
		Node<pair<char, int>> *right = pq.top();
		pq.pop();

		int newFreq = left->data.second + right->data.second;
		pq.push(makeHuffmanNode('\0', newFreq, left, right));
	}
	Node<pair<char, int>>* root = pq.top();

	unordered_map<char, string> huffmanCodes;
	traverseHuffmanTree(root, "", huffmanCodes);

	cout << "Huffman codes are: \n";
	for (unordered_map<char, string>::iterator it = huffmanCodes.begin(); it != huffmanCodes.end(); it++) {
		cout << it->first << " " << it->second << endl;
	}

	cout << endl << "Original string is: \n" << text << endl;

	string encodedString;
	for (int i = 0; i < text.length(); i++) {
		char temp = text[i];
		encodedString += huffmanCodes[temp];
	}

	cout << "\n-------------------------------------------------------------\n\nEncoded string is: \n\n" << encodedString << endl;
	int index = -1;
	cout << endl << "\n-------------------------------------------------------------\n\n Decoded string is: \n";
	while (index < (int)(encodedString.length() - 1)) {
		decodeLetter(root, index, encodedString);
	}
	cout << "\n\n" << "Original string has size " << (int)text.length() * 8 << " bits." << endl;
	cout << "Encoded string has size " << encodedString.length() << " bits." << endl;

	return root;
}

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
