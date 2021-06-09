#include "Quest.h"

using namespace std;

Quest::Quest() {}
Quest::~Quest() {}

istream& operator >> (istream& enter, Quest& request)
{
	enter >> request.r >> request.p >> request.q;
	return enter;
}

ostream& operator << (ostream& exit, Quest& request)
{
	cout << request.r << " " << request.p << " " << request.q << endl;
	return exit;
}
