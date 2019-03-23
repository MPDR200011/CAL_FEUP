#include "cute/cute.h"
#include "cute/ide_listener.h"
#include "cute/xml_listener.h"
#include "cute/cute_runner.h"
#include "Graph.h"
#include "Person.h"

void createNetwork(Graph<Person> & net1)
{
	Person p1("Ana",19);
	Person p2("Carlos",33);
	Person p3("Filipe", 20);
	Person p4("Ines", 18);
	Person p5("Maria", 24);
	Person p6("Rui",21);
	Person p7("Vasco",28);
	net1.addVertex(p1); net1.addVertex(p2);
	net1.addVertex(p3); net1.addVertex(p4);
	net1.addVertex(p5); net1.addVertex(p6); net1.addVertex(p7);
	net1.addEdge(p1,p2,0);
	net1.addEdge(p1,p3,0);
	net1.addEdge(p1,p4,0);
	net1.addEdge(p2,p5,0);
	net1.addEdge(p5,p6,0);
	net1.addEdge(p5,p1,0);
	net1.addEdge(p3,p6,0);
	net1.addEdge(p3,p7,0);
	net1.addEdge(p6,p2,0);
}

void test_addVertex() {
	Graph<Person> net1;
	Person p1("Ana",19);
	Person p2("Carlos",33);
	Person p3("Filipe", 20);
	Person p4("Ines", 18);
	net1.addVertex(p1); net1.addVertex(p2);
	net1.addVertex(p3); net1.addVertex(p4);
	ASSERT_EQUAL(false, net1.addVertex(p2));
	ASSERT_EQUAL(4, net1.getNumVertex());
}

void test_removeVertex() {
	Graph<Person> net1;
	Person p1("Ana",19);
	Person p2("Carlos",33);
	Person p3("Filipe", 20);
	Person p4("Ines", 18);
	net1.addVertex(p1); net1.addVertex(p2);
	net1.addVertex(p3); net1.addVertex(p4);
	ASSERT_EQUAL(true, net1.removeVertex(p2));
	ASSERT_EQUAL(false, net1.removeVertex(p2));
	ASSERT_EQUAL(3, net1.getNumVertex());
}

void test_addEdge() {
	Graph<Person> net1;
	Person p1("Ana",19);
	Person p2("Carlos",33);
	Person p3("Filipe", 20);
	Person p4("Ines", 18);
	Person p5("Maria", 24);
	net1.addVertex(p1); net1.addVertex(p2);
	net1.addVertex(p3); net1.addVertex(p4);
	ASSERT_EQUAL(true, net1.addEdge(p1,p2,0));
	ASSERT_EQUAL(true, net1.addEdge(p1,p3,0));
	ASSERT_EQUAL(true, net1.addEdge(p1,p4,0));
	ASSERT_EQUAL(false, net1.addEdge(p2,p5,0));
}

void test_removeEdge() {
	Graph<Person> net1;
	Person p1("Ana",19);
	Person p2("Carlos",33);
	Person p3("Filipe", 20);
	Person p4("Ines", 18);
	Person p5("Maria", 24);
	net1.addVertex(p1); net1.addVertex(p2);
	net1.addVertex(p3); net1.addVertex(p4);
	ASSERT_EQUAL(true, net1.addEdge(p1,p2,0));
	ASSERT_EQUAL(true, net1.addEdge(p1,p3,0));
	ASSERT_EQUAL(true, net1.addEdge(p1,p4,0));
	ASSERT_EQUAL(true, net1.addEdge(p2,p4,0));
	ASSERT_EQUAL(true, net1.removeEdge(p1,p3));
	ASSERT_EQUAL(false, net1.removeEdge(p1,p5));
	ASSERT_EQUAL(false, net1.removeEdge(p2,p3));
}


void test_dfs() {
	Graph<Person> net1;
	createNetwork(net1);
	vector<Person> v1 = net1.dfs();
	string names[] = {"Ana", "Carlos", "Maria", "Rui", "Filipe", "Vasco", "Ines"};
	for (unsigned i = 0; i < 7; i++)
		if (i < v1.size())
			ASSERT_EQUAL(names[i], v1[i].getName());
		else
			ASSERT_EQUAL(names[i], "(null)");
}

void test_bfs() {
	Graph<Person> net1;
	createNetwork(net1);
	vector<Person> v1 = net1.bfs(Person("Ana",19));
	string names[] = {"Ana", "Carlos", "Filipe", "Ines", "Maria", "Rui", "Vasco"};
	for (unsigned i = 0; i < 7; i++)
		if (i < v1.size())
			ASSERT_EQUAL(names[i], v1[i].getName());
		else
			ASSERT_EQUAL(names[i], "(null)");
}

void test_removeVertex_Again() {
	Graph<Person> net1;
	createNetwork(net1);
	Person p2("Carlos",33);
	ASSERT_EQUAL(true, net1.removeVertex(p2));
	vector<Person> v1=net1.dfs();
	string names[] = {"Ana", "Filipe", "Rui", "Vasco", "Ines", "Maria"};
	for (unsigned i = 0; i < 6; i++)
		ASSERT_EQUAL(names[i], v1[i].getName());
}

void test_removeEdge_Again() {
	Graph<Person> net1;
	createNetwork(net1);
	Person p5("Maria", 24);
	Person p6("Rui",21);
	ASSERT_EQUAL(true, net1.removeEdge(p5,p6));
	vector<Person> v1=net1.dfs();
	string names[] = {"Ana", "Carlos", "Maria", "Filipe", "Rui", "Vasco", "Ines"};
	for (unsigned i = 0; i < 7; i++)
		ASSERT_EQUAL(names[i], v1[i].getName());
}


void test_maxNewChildren() {
	Graph<Person> net1;
	Person p1("Ana",19);
	Person p2("Carlos",33);
	Person p3("Filipe", 20);
	Person p4("Ines", 18);
	Person p5("Maria", 24);
	Person p6("Rui",21);
	Person p7("Vasco",28);
	net1.addVertex(p1); net1.addVertex(p2);
	net1.addVertex(p3); net1.addVertex(p4);
	net1.addVertex(p5); net1.addVertex(p6); net1.addVertex(p7);
	net1.addEdge(p1,p2,0);
	net1.addEdge(p1,p3,0);
	net1.addEdge(p2,p5,0);
	net1.addEdge(p3,p4,0);
	net1.addEdge(p5,p6,0);
	net1.addEdge(p5,p1,0);
	net1.addEdge(p3,p6,0);
	net1.addEdge(p3,p7,0);
	net1.addEdge(p3,p2,0);
	Person pt;
	ASSERT_EQUAL(3, net1.maxNewChildren(Person("Ana",19), pt));
	ASSERT_EQUAL("Filipe", pt.getName());
}



void test_isDAG() {
	Graph<int> myGraph;

	myGraph.addVertex(0);myGraph.addVertex(1); myGraph.addVertex(2);
	myGraph.addVertex(3); myGraph.addVertex(4); myGraph.addVertex(5);
	myGraph.addEdge(1, 2, 0);
	myGraph.addEdge(2, 5, 0);
	myGraph.addEdge(5, 4, 0);
	myGraph.addEdge(4, 1, 0);
	myGraph.addEdge(5, 1, 0);
	myGraph.addEdge(2, 3, 0);
	myGraph.addEdge(3, 1, 0);
	myGraph.addEdge(0, 4, 0);

	ASSERT_EQUAL(false, myGraph.isDAG());

	myGraph.removeEdge(4, 1);
	myGraph.removeEdge(5, 1);
	myGraph.removeEdge(2, 3);

	ASSERT_EQUAL(true, myGraph.isDAG());

	myGraph.addEdge(1, 4, 0);

	ASSERT_EQUAL(true, myGraph.isDAG());
}


void test_topsort() {
	Graph<int> myGraph;
	myGraph.addVertex(1); myGraph.addVertex(2); myGraph.addVertex(3); myGraph.addVertex(4);
	myGraph.addVertex(5); myGraph.addVertex(6); myGraph.addVertex(7);
	myGraph.addEdge(1, 2, 0);
	myGraph.addEdge(1, 4, 0);
	myGraph.addEdge(1, 3, 0);
	myGraph.addEdge(2, 5, 0);
	myGraph.addEdge(2, 4, 0);
	myGraph.addEdge(3, 6, 0);
	myGraph.addEdge(4, 3, 0);
	myGraph.addEdge(4, 6, 0);
	myGraph.addEdge(4, 7, 0);
	myGraph.addEdge(5, 4, 0);
	myGraph.addEdge(5, 7, 0);
	myGraph.addEdge(7, 6, 0);

	vector<int> topOrder;

	topOrder = myGraph.topsort();
	stringstream ss;
	for( unsigned int i = 0; i < topOrder.size(); i++)
		ss << topOrder[i] << " ";
	ASSERT_EQUAL("1 2 5 4 3 7 6 ", ss.str());

	//para testar a inclusao de um ciclo no grafo!
	myGraph.addEdge(3, 1, 0);

	topOrder = myGraph.topsort();
	ss.str("");
	for( unsigned int i = 0; i < topOrder.size(); i++)
		ss << topOrder[i] << " ";
	ASSERT_EQUAL("", ss.str());
}


bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	s.push_back(CUTE(test_addVertex));
	s.push_back(CUTE(test_addEdge));
	s.push_back(CUTE(test_removeEdge));
	s.push_back(CUTE(test_removeVertex));
	s.push_back(CUTE(test_dfs));
	s.push_back(CUTE(test_removeVertex_Again));
	s.push_back(CUTE(test_removeEdge_Again));
	s.push_back(CUTE(test_bfs));
	s.push_back(CUTE(test_topsort));
	s.push_back(CUTE(test_maxNewChildren));
	s.push_back(CUTE(test_isDAG));

	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}

