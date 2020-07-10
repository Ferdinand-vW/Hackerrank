#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Message {
  private:
  std::string text_;
  int n_;
public: 
    Message() {}
    Message(const string &text,int n) {
     text_ = text;
     n_ = n; 
    }
    const string& get_text() {
        return text_;
    }

    const int &get_id() {
      return n_;
    }

    friend bool operator< (Message m1,Message m2) {
      return m1.get_id() < m2.get_id();
    }
};

class MessageFactory {
  private:
  int n;
public:
    MessageFactory() { n = 0; }
    Message create_message(const string& text) {
      n++;
      return Message(text,n);
    }
};

class Recipient {
public:
    Recipient() {}
    void receive(const Message& msg) {
        messages_.push_back(msg);
    }
    void print_messages() {
        fix_order();
        for (auto& msg : messages_) {
            cout << msg.get_text() << endl;
        }
        messages_.clear();
    }
private:
    void fix_order() {
        sort(messages_.begin(), messages_.end());
    }
    vector<Message> messages_;
};

class Network {
public:
    static void send_messages(vector<Message> messages, Recipient& recipient) {
    // simulates the unpredictable network, where sent messages might arrive in unspecified order
        random_shuffle(messages.begin(), messages.end());         
        for (auto msg : messages) {
            recipient.receive(msg);
        }
    }
};



int main() {
    MessageFactory message_factory;
    Recipient recipient;
    vector<Message> messages;
    string text;
    while (getline(cin, text)) {
        messages.push_back(message_factory.create_message(text));
    }
    Network::send_messages(messages, recipient);
    recipient.print_messages();
}
