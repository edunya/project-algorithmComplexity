#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <chrono>
#include <string>

using namespace std;

// -------------------
// İş Zamanlama (Shortest job first)
// -------------------
struct Job {
    int id;
    int time;
};

void jobScheduling(vector<Job>& jobs) {
    sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) {
        return a.time < b.time;
    });

    cout << "Siralama (kisa is once): ";
    for (auto& j : jobs) cout << "J" << j.id << "(" << j.time << ") ";
    cout << "\n";

    long long toplamBitis = 0;
    int cur = 0;

    cout << "Tamamlanma sureleri: ";
    for (auto& j : jobs) {
        cur += j.time;
        toplamBitis += cur;
        cout << cur << " ";
    }
    cout << "\nOrtalama tamamlanma: " << (double)toplamBitis / jobs.size() << "\n";
}

// -------------------
// Aktivite Zamanlama
// -------------------
struct Activity {
    int id;
    int start;
    int finish;
};

void activityScheduling(vector<Activity>& acts) {
    sort(acts.begin(), acts.end(), [](const Activity& a, const Activity& b) {
        return a.finish < b.finish;
    });

    cout << "Finish'e gore sirali: ";
    for (auto& a : acts) cout << "a" << a.id << "[" << a.start << "-" << a.finish << "] ";
    cout << "\n";

    cout << "Secilen aktiviteler: ";
    int last = 0;
    cout << "a" << acts[last].id << " ";
    for (int i = 1; i < (int)acts.size(); i++) {
        if (acts[i].start >= acts[last].finish) {
            cout << "a" << acts[i].id << " ";
            last = i;
        }
    }
    cout << "\n";
}

// -------------------
// Huffman (encode / decode)
// -------------------
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
    Node(Node* l, Node* r) : ch('\0'), freq(l->freq + r->freq), left(l), right(r) {}
};

struct Cmp {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq; // min-heap
    }
};

void buildCodes(Node* root, string path, string codes[256]) {
    if (!root) return;

    if (!root->left && !root->right) {
        codes[(unsigned char)root->ch] = (path.empty() ? "0" : path);
        return;
    }
    buildCodes(root->left, path + "0", codes);
    buildCodes(root->right, path + "1", codes);
}

string encodeText(const string& text, string codes[256]) {
    string bits;
    for (char c : text) bits += codes[(unsigned char)c];
    return bits;
}

string decodeBits(Node* root, const string& bits) {
    string out;
    Node* cur = root;

    for (char b : bits) {
        if (!cur) return "(decode hata)";

        cur = (b == '0') ? cur->left : cur->right;
        if (cur && !cur->left && !cur->right) {
            out.push_back(cur->ch);
            cur = root;
        }
    }
    return out;
}

void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

void huffmanDemo(const string& text) {
    int freq[256] = {0};
    for (char c : text) freq[(unsigned char)c]++;

    priority_queue<Node*, vector<Node*>, Cmp> pq;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) pq.push(new Node((char)i, freq[i]));
    }

    if (pq.empty()) {
        cout << "Huffman: metin bos\n";
        return;
    }

    while ((int)pq.size() > 1) {
        Node* a = pq.top(); pq.pop();
        Node* b = pq.top(); pq.pop();
        pq.push(new Node(a, b));
    }

    Node* root = pq.top();

    string codes[256];
    buildCodes(root, "", codes);

    cout << "Karakter kodlari:\n";
    for (int i = 0; i < 256; i++) {
        if (!codes[i].empty()) {
            cout << "  '" << (char)i << "' : " << codes[i] << "\n";
        }
    }

    string bits = encodeText(text, codes);
    cout << "Encode bits: " << bits << "\n";

    string decoded = decodeBits(root, bits);
    cout << "Decode metin: " << decoded << "\n";

    freeTree(root);
}

int main() {
    cout << "GREEDY ALGORITMALAR\n";
    cout << "-------------------\n";

    // 1) İş Zamanlama
    vector<Job> jobs = { {1,15}, {2,8}, {3,3}, {4,10} };
    auto t1 = chrono::high_resolution_clock::now();
    cout << "[1] Is Zamanlama\n";
    jobScheduling(jobs);
    auto t2 = chrono::high_resolution_clock::now();
    cout << "Sure: " << chrono::duration_cast<chrono::microseconds>(t2 - t1).count() << " us\n\n";

    // 2) Aktivite
    vector<Activity> acts = {
        {1,1,4},{2,3,5},{3,0,6},{4,5,7},{5,3,8},
        {6,5,9},{7,6,10},{8,8,11},{9,8,12},{10,2,13},{11,12,14}
    };
    t1 = chrono::high_resolution_clock::now();
    cout << "[2] Aktivite Zamanlama\n";
    activityScheduling(acts);
    t2 = chrono::high_resolution_clock::now();
    cout << "Sure: " << chrono::duration_cast<chrono::microseconds>(t2 - t1).count() << " us\n\n";

    // 3) Huffman
    cout << "[3] Huffman Encode/Decode\n";
    string text = "ABBCCCDDDDEEEEEFF";
    cout << "Girdi metin: " << text << "\n";
    t1 = chrono::high_resolution_clock::now();
    huffmanDemo(text);
    t2 = chrono::high_resolution_clock::now();
    cout << "Sure: " << chrono::duration_cast<chrono::microseconds>(t2 - t1).count() << " us\n";

    return 0;
}
