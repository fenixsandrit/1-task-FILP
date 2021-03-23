#include <iostream>
#include <fstream>
#include <malloc.h>
#include <windows.h>
#include <map>
#include <time.h>
using namespace std;
class Block {
int len = 0;
int count_b = 0;
struct Note{
    char* word = new char[201];
    Note* next = nullptr;
};
Note data;

public:

    ~Block()
	{
        Note *temp = &data;
        Note *temp_next = data.next;
        delete temp;
        while(temp_next != nullptr){
            temp = temp_next;
            temp_next = temp_next->next;
            delete temp;
        }
	}

    class Iterator;

    Iterator begin(){return &data;}

    Iterator end(){
        Note *temp = &data;
        while(temp != nullptr)temp = temp->next;
        return temp;
    }

    int get_length(){return len;}

    int get_count_b(){return count_b;}

    void Fill(char* v){
        int i=0;
        Note *temp = &data;
        ifstream in(v);
        char symb;
        count_b++;
        while((symb = in.get()) != EOF) {
        if(i == 200){
            temp->word[200] = '\0';
            Note *n = new Note;
            temp->next = n;
            temp = n;
            i = 0;
            count_b++;
        }
        temp->word[i] = symb;
        len++;
        i++;

        }

            temp->word[i] = '\0';


        in.close();
    }
    void Print(){
        int i=0;
        Note *temp = &data;
        char symb = data.word[0];
        while(symb != '\0') {
        cout << symb;
        i++;
        if(i == 200){
            temp = temp->next;
            i = 0;
        }
        symb = temp->word[i];
        }
        cout << endl;
    }

    class Iterator{

        Note* cur;

    public:

        Iterator(Note* first) : cur(first){}

        Note& operator++ (int){
            cur = cur->next;
            return *cur;
        }

        bool operator!= (const Iterator& it){ return cur != it.cur; }

        bool operator== (const Iterator& it){ return cur == it.cur; }

        char* operator* (){return cur->word;}

    };

};
class MyMap{

    struct m_v{
        char* value = new char[50];
        int key;
        m_v* next = nullptr;
        bool full = false;
    };

    m_v m;

    int length = 0;

public:

    ~MyMap()
    {
        m_v *temp = &m;
        m_v *temp_next = m.next;
        delete temp;
        while(temp_next != nullptr){
            temp = temp_next;
            temp_next = temp_next->next;
            delete temp;
        }
	}

    class Iterator;

    Iterator begin(){return &m;}

    Iterator end(){
        m_v *temp = &m;
        while(temp != nullptr)temp = temp->next;
        return temp;
    }

    void add(char *v,int k){
            if(m.full == false){                //если в MyMaP нет элементов
              m.key  = k;
              int i=0;
              for(i;i<strlen(v);i++)m.value[i] = v[i];
              m.value[i] = 0;
              m.full = true;
              length++;
            }
            else {                              //если элемент который мы хотим добавить уже существует или требуется добавить новый узел
                bool in = false;                //флаг проверяющий есть ли данный элемент в map; true - есть, false - нет.
                m_v *temp = &m;
                while(temp != nullptr){
                        bool flag=true;
                        {                       //сравнение двух строк
                                int i=0;
                                for(i;i<strlen(v) && temp->value[i]!='\0';i++)
                                  if(temp->value[i]!=v[i]){flag = false; break; }


                                if(temp->value[i] != '\0' || i != strlen(v))flag = false;
                        }
                        if(flag){temp->key = k; in = true; break;}
                        temp = temp->next;
                    }

                if(!in){//добавление нового узла
                    temp = &m;
                    while(temp->next != nullptr)temp = temp->next;
                    m_v *addition = new m_v;
                    temp->next = addition;

                    addition->key = k;
                    int i=0;
                    for(i;i<strlen(v);i++)addition->value[i] = v[i];

                    addition->value[i] = 0;
                    addition->full = true;
                    length++;

                    }
            }

    }

    int get_key(char *v){
        if(m.full){
        m_v *temp = &m;
        while(temp != nullptr){
                bool flag=true;
                {//сравнение двух строк
                    int i=0;
                    for(i;i<strlen(v) && temp->value[i]!='\0';i++)
                    if(temp->value[i]!=v[i]){flag = false; break; }

                    if(temp->value[i] != '\0' || i != strlen(v))flag = false;
                }
                    if(flag){return temp->key ; break;}

                temp = temp->next;
            }
        }
            return  -2066666666;

    }

    void see_all(){
        if(m.full){
        m_v *temp = &m;
        while(temp != nullptr){
                cout << "(" << temp->value << ";" << temp->key << ")" << endl;
                temp = temp->next;}
                cout << endl;
        }
    }
    bool find_in(char* v){return -2066666666 != get_key(v);}

    int get_length(){return length;}

    class Iterator{
        m_v* cur;
    public:
        Iterator(m_v* first) : cur(first){}

        m_v& operator++ (int){
            cur = cur->next;
            return *cur;
        }

        bool operator!= (const Iterator& it){ return cur != it.cur; }

        bool operator== (const Iterator& it){ return cur == it.cur; }

        char* operator* (){
            return cur->value;
        }
    };
};

void test_my_map(){
    Block b;
    MyMap m;
    b.Fill("in.txt");
    auto it = Block::Iterator(b.begin());
    char *temp;
    int i=0;
    char* buff = new char[50];
    bool lett_flag = false;
    while(it != b.end()){
    temp = *it;

    for(int j=0;j<strlen(temp);j++){
        char ch = temp[j];
        if( (ch>=97 && ch<=122) || (ch>=65 && ch<=90)){
            lett_flag = true;
            if(ch>=65 && ch<=90)ch+=32;
            buff[i] = ch;
            i++;
        }
        else if(ch == '\'' && lett_flag){
            buff[i] = ch;
            i++;
        }
        else
        {
            if(lett_flag){
                 buff[i] = '\0';
                 {
                    if(!m.find_in(buff)) m.add(buff,1);
                    else m.add(buff,m.get_key(buff)+1);
                 }
            }
            lett_flag = false;
            i=0;
        }

    }
    it++;
    }

    int sum_words = 0;//количество слов
    auto it_m = MyMap::Iterator(m.begin());
    while(it_m != m.end()){
        sum_words+=m.get_key(*it_m);
        it_m++;
    }
}

void test_default_map(){
    map<char*,int> m;

    Block b;
    b.Fill("in.txt");
    auto it = Block::Iterator(b.begin());
    char *temp;
    int i=0;
    char* buff = new char[50];
    bool lett_flag = false;

    while(it != b.end()){
    temp = *it;

    for(int j=0;j<strlen(temp);j++){
        char ch = temp[j];
        if( (ch>=97 && ch<=122) || (ch>=65 && ch<=90)){
            lett_flag = true;
            if(ch>=65 && ch<=90)ch+=32;
            buff[i] = ch;
            i++;
        }
        else if(ch == '\'' && lett_flag){
            buff[i] = ch;
            i++;
        }
        else
        {
            if(lett_flag){
                buff[i] = '\0';
                m[buff] = m[buff] + 1;
            }
            lett_flag = false;
            i=0;
        }

    }
    it++;
    }

    int sum_words = 0;//Количество слов
    for(auto it_m = m.begin(); it_m != m.end(); ++it_m)sum_words += it_m->second;

}
int main()
{
    clock_t start1 = clock();
    test_my_map();
    clock_t end1 = clock();
    clock_t start2 = clock();
    test_default_map();
    clock_t end2 = clock();
    cout << "My_Map time: " << (double)(end1 - start1) << "ms"<< endl << "Default_Map time: " << (double)(end2 - start2) << "ms" <<  endl;
    return 0;
}
