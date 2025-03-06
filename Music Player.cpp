#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Node {
    string song;
    Node* next;
    Node* prev;
    Node(string s) : song(s), next(nullptr), prev(nullptr) {}
};

struct Queue {
    Node* front;
    Node* rear;
    Queue() : front(nullptr), rear(nullptr) {}
    
    void enqueue(string song) {
        Node* newNode = new Node(song);
        if (!rear) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        cout << "Added to queue: " << song << endl;
    }
    
    void dequeue() {
        if (!front) {
            cout << "Queue is empty!" << endl;
            return;
        }
        Node* temp = front;
        cout << "Now playing: " << front->song << endl;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
    }
    
    void showQueue() {
        if (!front) {
            cout << "Queue is empty!" << endl;
            return;
        }
        cout << "Upcoming Songs:" << endl;
        Node* temp = front;
        while (temp) {
            cout << temp->song << endl;
            temp = temp->next;
        }
    }
};

class MusicPlayer {
private:
    Node* head;
    Queue songQueue;
public:
    MusicPlayer() : head(nullptr) {}
    
    void addSong(string song) {
        Node* newNode = new Node(song);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
            newNode->prev = temp;
        }
        ofstream file("playlist.txt", ios::app);
        file << song << endl;
        file.close();
        cout << "Song added: " << song << endl;
    }
    
    void showPlaylist() {
        if (!head) {
            cout << "Playlist is empty!" << endl;
            return;
        }
        Node* temp = head;
        cout << "Playlist:" << endl;
        while (temp) {
            cout << temp->song << endl;
            temp = temp->next;
        }
    }
    
    void playSong(string song) {
        Node* temp = head;
        while (temp) {
            if (temp->song == song) {
                cout << "Now Playing: " << song << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Song not found!" << endl;
    }
    
    void addToQueue(string song) {
        songQueue.enqueue(song);
    }
    
    void playNext() {
        songQueue.dequeue();
    }
    
    void showQueue() {
        songQueue.showQueue();
    }
};

int main() {
    MusicPlayer player;
    int choice;
    string song;
    
    do {
        cout << "\n1. Add Song\n2. Show Playlist\n3. Play Song\n4. Add to Queue\n5. Play Next\n6. Show Queue\n7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1:
                cout << "Enter song name: ";
                getline(cin, song);
                player.addSong(song);
                break;
            case 2:
                player.showPlaylist();
                break;
            case 3:
                cout << "Enter song name to play: ";
                getline(cin, song);
                player.playSong(song);
                break;
            case 4:
                cout << "Enter song name to add to queue: ";
                getline(cin, song);
                player.addToQueue(song);
                break;
            case 5:
                player.playNext();
                break;
            case 6:
                player.showQueue();
                break;
            case 7:
                cout << "Exiting..." << endl;
                break;
            
        }
    } while (choice != 7);
    
    return 0;
}
