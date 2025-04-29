// VirtualMemorySimulator_FLTK.cpp
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Multiline_Output.H>
#include <sstream>
#include <vector>
#include <queue>
#include <set>
#include <unordered_map>
#include <list>

Fl_Input *frameInput, *pageInput;
Fl_Choice *algoChoice;
Fl_Multiline_Output *output;

void fifoSim(const std::vector<int>& pages, int capacity, std::ostringstream &out) {
    std::set<int> s;
    std::queue<int> q;
    int faults = 0;
    for (int page : pages) {
        if (s.find(page) == s.end()) {
            if (s.size() == capacity) {
                int removed = q.front(); q.pop();
                s.erase(removed);
                out << "Page " << removed << " removed\n";
            }
            s.insert(page);
            q.push(page);
            faults++;
            out << "Page " << page << " added (Fault)\n";
        } else {
            out << "Page " << page << " hit\n";
        }
    }
    out << "Total Page Faults: " << faults << "\n";
}

void lruSim(const std::vector<int>& pages, int capacity, std::ostringstream &out) {
    std::unordered_map<int, std::list<int>::iterator> map;
    std::list<int> lru;
    int faults = 0;
    for (int page : pages) {
        if (map.find(page) == map.end()) {
            if ((int)lru.size() == capacity) {
                int last = lru.back(); lru.pop_back();
                map.erase(last);
                out << "Page " << last << " removed\n";
            }
            lru.push_front(page);
            map[page] = lru.begin();
            faults++;
            out << "Page " << page << " added (Fault)\n";
        } else {
            lru.erase(map[page]);
            lru.push_front(page);
            map[page] = lru.begin();
            out << "Page " << page << " hit\n";
        }
    }
    out << "Total Page Faults: " << faults << "\n";
}

void simulate_cb(Fl_Widget*, void*) {
    std::ostringstream out;
    std::string pageStr = pageInput->value();
    std::istringstream ss(pageStr);
    std::vector<int> pages;
    int x;
    while (ss >> x) pages.push_back(x);

    int frames = std::atoi(frameInput->value());
    int algo = algoChoice->value();

    if (algo == 0) fifoSim(pages, frames, out);
    else lruSim(pages, frames, out);

    output->value(out.str().c_str());
}

void clear_cb(Fl_Widget*, void*) {
    frameInput->value("");
    pageInput->value("");
    output->value("");
}

int main(int argc, char **argv) {
    Fl_Window *win = new Fl_Window(500, 400, "Virtual Memory Simulator - FLTK");

    frameInput = new Fl_Input(150, 20, 100, 25, "Frame Size:");
    pageInput = new Fl_Input(150, 60, 300, 25, "Page Sequence:");

    algoChoice = new Fl_Choice(150, 100, 120, 25, "Algorithm:");
    algoChoice->add("FIFO");
    algoChoice->add("LRU");
    algoChoice->value(0);

    Fl_Button *runBtn = new Fl_Button(150, 140, 120, 30, "Run Simulation");
    runBtn->callback(simulate_cb);

    Fl_Button *clearBtn = new Fl_Button(290, 140, 80, 30, "Clear");
    clearBtn->callback(clear_cb);

    output = new Fl_Multiline_Output(20, 190, 460, 180, "Output:");

    win->end();
    win->show(argc, argv);
    return Fl::run();
}
