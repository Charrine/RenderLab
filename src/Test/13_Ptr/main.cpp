#include <CppUtil/Basic/HeapObj.h>
#include <CppUtil/Basic/LambdaOp.h>

#include <iostream>
#include <vector>
#include <string>

using namespace CppUtil::Basic;
using namespace std;

// ������ģ�嶨�壬�� ImplT ���� HeapObj ��
// �����ֱ���� Ptr, PtrC, WPtr, WPtrC
template<typename ImplT>
class Node: public HeapObj {
protected:// ���캯�� protected������д��Ӧ�� New ����
	Node(Ptr<ImplT> parent = nullptr)
		: parent(parent) { }

protected:// ����һ��Ĭ�ϵ�����������
	virtual ~Node() { cout << "destruct Node" << endl; }

public:
	const Ptr<ImplT> GetParent() { return parent.lock(); }
	const PtrC<ImplT> GetParent() const { return parent.lock(); }
	vector<Ptr<ImplT>> & GetChildren() { return children; }
	const vector<Ptr<ImplT>> & GetChildren() const { return children; }

protected:
	virtual void Init() override {
		cout << "Init Node" << endl;
		if (!parent.expired())
			parent.lock()->children.push_back(This<ImplT>());
	}

private:
	WPtr<ImplT> parent;
	vector<Ptr<ImplT>> children;
};

class SObj final : public Node<SObj> {
public:// ���� New ��Ҫ�õ����캯��������Ҫ public
	// ͨ�� New<SObj>(const string & name, Ptr<SObj> parent = nullptr) ������
	SObj(const string & name, Ptr<SObj> parent = nullptr)
		: name(name), Node<SObj>(parent) { }

public:
	// ͨ��дһ�� static �����������û�ʹ�ã������� IDE��
	static const Ptr<SObj> New(const string & name, Ptr<SObj> parent = nullptr) {
		return CppUtil::Basic::New<SObj>(name, parent);
	}

public:
	void Print(int depth = 0) const {
		for (int i = 0; i < depth; i++)
			cout << " ";

		cout << name << endl;
		for (const auto child : GetChildren())
			child->Print(depth + 1);
	}

protected:
	virtual void Init() override {
		cout << "Init SObj " << name << ", ";
		Node<SObj>::Init();
	}

private:
	virtual ~SObj() { cout << "destruct SObj " << name << endl; }// ��ֹ�Ѷ���Ĵ���

public:
	string name;
};

int main() {
	const auto a = New<SObj>("A");
	const auto ab = New<SObj>("B", a);
	const auto ac = New<SObj>("C", a);
	const auto abd = SObj::New("D", ab);
	const auto ace = SObj::New("E", ac);

	a->Print();


	Ptr<Op> op = LambdaOp_New([=]() {
		cout << abd->name << endl;
	});
	cout << typeid(*op).name() << endl;
	op->Run();

	return 0;
}