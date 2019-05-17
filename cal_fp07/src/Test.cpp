#include "cute/cute.h"
#include "cute/ide_listener.h"
#include "cute/xml_listener.h"
#include "cute/cute_runner.h"


#include <iostream>
#include <string>

#include "Graph.h"
using namespace std;

Graph<int> createTestGraph()
{
	Graph<int> myGraph;

	for(int i = 1; i < 8; i++)
		myGraph.addVertex(i);

	myGraph.addEdge(1, 2, 2);
	myGraph.addEdge(1, 4, 7);
	myGraph.addEdge(2, 4, 3);
	myGraph.addEdge(2, 5, 5);
	myGraph.addEdge(3, 1, 2);
	myGraph.addEdge(3, 6, 5);
	myGraph.addEdge(4, 3, 1);
	myGraph.addEdge(4, 5, 1);
	myGraph.addEdge(4, 7, 4);
	myGraph.addEdge(5, 7, 2);
	myGraph.addEdge(6, 4, 3);
	myGraph.addEdge(7, 6, 4);

	// to force undirected graph...
	myGraph.addEdge(2, 1, 2);
	myGraph.addEdge(4, 1, 7);
	myGraph.addEdge(4, 2, 3);
	myGraph.addEdge(5, 2, 5);
	myGraph.addEdge(1, 3, 2);
	myGraph.addEdge(6, 3, 5);
	myGraph.addEdge(3, 4, 1);
	myGraph.addEdge(5, 4, 1);
	myGraph.addEdge(7, 4, 4);
	myGraph.addEdge(7, 5, 2);
	myGraph.addEdge(4, 6, 3);
	myGraph.addEdge(6, 7, 4);
	return myGraph;
}


void testPrim() {
	Graph<int> graph = createTestGraph();
	vector<Vertex<int>* > res = graph.calculatePrim();

	stringstream ss;
	for(unsigned int i = 0; i < res.size(); i++)
	{
		ss << res[i]->getInfo() << "<-";
		cout << res[i]->getInfo() << "<-";

		if ( res[i]->getPath() != NULL )
		{
			Vertex<int>* v = res[i]->getPath();
			ss << v->getInfo();
			cout << v->getInfo();
		}

		ss << "|";
		cout << "|";
	}

	cout << endl << endl;
	//cout << ss.str() << endl;

//	ASSERT_EQUAL("1<-|2<-1|3<-4|4<-2|5<-4|6<-7|7<-5|", ss.str());
	ASSERT_EQUAL("1<-|2<-1|3<-1|4<-3|5<-4|6<-4|7<-5|", ss.str());
}

void testKruskal() {
	Graph<int> graph = createTestGraph();
	vector<Vertex<int>* > res = graph.calculateKruskal();

	stringstream ss;
	for(unsigned int i = 0; i < res.size(); i++)
	{
		ss << res[i]->getInfo() << "<-";
		cout << res[i]->getInfo() << "<-";

		if ( res[i]->getPath() != NULL )
		{
			Vertex<int>* v = res[i]->getPath();
			ss << v->getInfo();
			cout << v->getInfo();
		}

		ss << "|";
		cout << "|";
	}

	cout << endl << endl;
	//cout << ss.str() << endl;

//	ASSERT_EQUAL("1<-3|2<-1|3<-4|4<-6|5<-4|6<-|7<-5|", ss.str());
//	ASSERT_EQUAL("1<-3|2<-1|3<-4|4<-5|5<-7|6<-4|7<-|", ss.str());
	ASSERT_EQUAL("1<-|2<-1|3<-1|4<-3|5<-4|6<-4|7<-5|", ss.str());
	// Nota: a melhorar esta verficacao (o que interessa sao as arestas serem selecionadas)
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	s.push_back(CUTE(testPrim));
	s.push_back(CUTE(testKruskal));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
