/**
 Assignment 1
 hw1.cpp
 Dhishan Amaranath
 N16909360
 **/

#include <iostream>
#include <cassert>
#include <string>

using namespace std;

class PrepaidAccount{
public:
    PrepaidAccount(const string &phone);
    PrepaidAccount(){phoneNumber = ""; balance = 0;};
    void AddBalance(double amount);
    float PayForCall(int callDuration, double tariff);
    const string PhoneNumber() const{return phoneNumber;};
    const float Balance() const{return balance;};

private:
    string phoneNumber;
    float balance;
    
};

class AccountStore{
public:
    typedef PrepaidAccount Item;
    static const int CAPACITY = 100;
    AccountStore(){size = 0;};
    int removeAccount(const string &phone);
    void insertAccount(const Item &);
    int getSize() const{return size;};
    Item getAccount(int) const;
    
private:
    Item data[CAPACITY];
    int size;
    
};

int CompareAccounts(const PrepaidAccount &a1,const PrepaidAccount &a2);

string getRandomNumber(){
    string number = to_string(((long)rand() << sizeof(int)*8) | rand());
    number.resize(10, '0');
    return number;
}

int main(int argc, const char * argv[]) {
    
    srand((int)time(NULL));
    
    PrepaidAccount prepaidAccount1(getRandomNumber());
    PrepaidAccount prepaidAccount2(getRandomNumber());
    PrepaidAccount prepaidAccount3(getRandomNumber());
    PrepaidAccount prepaidAccount4(getRandomNumber());
    PrepaidAccount prepaidAccount5(getRandomNumber());
    
    prepaidAccount1.AddBalance(rand() % 50 + 50);
    prepaidAccount2.AddBalance(rand() % 50 + 50);
    prepaidAccount3.AddBalance(rand() % 50 + 50);
    prepaidAccount4.AddBalance(rand() % 50 + 50);
    prepaidAccount5.AddBalance(rand() % 50 + 50);
    
    prepaidAccount1.PayForCall(rand() % 190 + 10, (double)((rand() % 5) / 10.0));
    prepaidAccount2.PayForCall(rand() % 190 + 10, (double)((rand() % 5) / 10.0));
    prepaidAccount3.PayForCall(rand() % 190 + 10, (double)((rand() % 5) / 10.0));
    prepaidAccount4.PayForCall(rand() % 190 + 10, (double)((rand() % 5) / 10.0));
    prepaidAccount5.PayForCall(rand() % 190 + 10, (double)((rand() % 5) / 10.0));
    
    AccountStore accountStore;
    
    accountStore.insertAccount(prepaidAccount1);
    accountStore.insertAccount(prepaidAccount2);
    accountStore.insertAccount(prepaidAccount3);
    accountStore.insertAccount(prepaidAccount4);
    accountStore.insertAccount(prepaidAccount5);
    
    cout << "Accounts" << endl;
    cout << accountStore.getAccount(0).PhoneNumber() << endl;
    cout << accountStore.getAccount(1).PhoneNumber() << endl;
    cout << accountStore.getAccount(2).PhoneNumber() << endl;
    cout << accountStore.getAccount(3).PhoneNumber() << endl;
    cout << accountStore.getAccount(4).PhoneNumber() << endl;
    cout << endl;
    
    cout << "Balance" << endl;
    cout << accountStore.getAccount(0).Balance() << endl;
    cout << accountStore.getAccount(1).Balance() << endl;
    cout << accountStore.getAccount(2).Balance() << endl;
    cout << accountStore.getAccount(3).Balance() << endl;
    cout << accountStore.getAccount(4).Balance() << endl;
    
    
    return 0;
}

PrepaidAccount::PrepaidAccount(const string &phone){
    assert(phone.size() == 10);
    phoneNumber = phone;
    balance = 0.0;
}

void PrepaidAccount::AddBalance(double amount){
    assert(amount > 0);
    balance += amount;
}

float PrepaidAccount::PayForCall(int callDuration, double tariff){
    float cost;
    cost = (callDuration/60.0) * tariff;
    if (balance - cost < 0){
        return -1;
    }
    balance -= cost;
    return cost;
}

int CompareAccounts(const PrepaidAccount &a1,const PrepaidAccount &a2){
    return a1.PhoneNumber().compare(a2.PhoneNumber());
}

void AccountStore::insertAccount(const Item &prepaidAccount){
    assert(size < AccountStore::CAPACITY);
    int pos = 0;
    for (pos = 0; pos < size; pos++) {
        if (CompareAccounts(data[pos], prepaidAccount) > 0) {
            break;
        }
    }
    for (int index = size -1; index >= pos; index--) {
        data[index + 1] = data[index];
    }
    data[pos] = prepaidAccount;
    size++;
}

int AccountStore::removeAccount(const string &phone){
    assert(getSize() > 0);
    int pos = 0;
    for (pos = 0; pos < size; pos++) {
        if (data[pos].PhoneNumber().compare(phone) == 0) {
            break;
        }
    }
    if (pos == size) {
        return -1;
    }
    for (int index = pos; index < size - 1; index++) {
        data[index] = data[index + 1];
    }
    size--;
    return 0;
}


AccountStore::Item AccountStore::getAccount(int i) const{
    assert(i<getSize());
    return data[i];
}