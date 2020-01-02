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