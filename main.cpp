#include <iostream>
#include <cstdlib>
#include <SFML/Audio.hpp>
#include <conio.h>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include "DLL.h"

using namespace std;
class Surah
{
private:
    string audioFile;
    string name;
    string type;
    size_t id;
public:
    Surah(string name = "", string audioFile = "", string type = "") : name(name), audioFile(audioFile),type(type) {}

    string get_name() const
    {
        return name;
    }
    void set_surah_name(string name)
    {
        this->name = name;
    }

    string get_surah_type() const
    {
        return type;
    }
    void set_surah_type(string type)
    {
        this->type = type;
    }

    string getAudioFile() const
    {
        return audioFile;
    }
    void set_audio(string audioFile)
    {
        this->audioFile = audioFile;
    }
    void print_surah_line(size_t id, const Surah& surah)
    {
        std::cout << std::left
                  << "| " << std::setw(10) << id
                  << "| " << std::setw(30) << name
                  << "| " << std::setw(20) << type
                  << "| " << std::setw(80) << audioFile
                  << "| \n";
    }
    void read_surah()
    {
        cout<<"Enter Surah name : ";
        cin>>name;
        cout<<"Enter Surah type : ";
        cin>>type;
        cout<<"Enter Surah path : ";
        cin>>audioFile;
    }
    bool operator==(const Surah& other) const
    {
        return (name == other.name) &&
               (type == other.type) &&
               (audioFile == other.audioFile) &&
               (id == other.id);
    }
};
class Playlist
{
private:
    DLL<Surah> surahs;
    string name;
    size_t id;
public:
    Playlist(string name = "") : name(name) {}

    Playlist(const Playlist& other) : surahs(other.surahs), name(other.name), id(other.id) {}

    Playlist& operator=(const Playlist& other)
    {
        if (this != &other)
        {
            surahs = other.surahs;
            name = other.name;
            id = other.id;
        }
        return *this;
    }
    bool operator==(const Playlist& other) const
    {
        if (name != other.name)
        {
            return false;
        }
        if (surahs.get_length() != other.surahs.get_length())
        {
            return false;
        }
        return true;
    }
    string get_name()const
    {
        return name;
    }
    void set_playlist_name()
    {
        this->name = name;
    }
    void print_line(size_t id, const Playlist& playlist)
    {
        std::cout << std::left
                  << "| " << std::setw(10) << id
                  << "| " << std::setw(30) << name
                  << "| \n";
    }
    void surahs_header()
    {
        std::cout << std::string(149, '-') << std::endl;
        std::cout<<std::left
                 <<"| "<<std::setw(10)<<"ID"
                 <<"| "<<std::setw(30)<<"Surah Name"
                 <<"| "<<std::setw(20)<<"Surah type"
                 <<"| "<<std::setw(80)<<"Path"
                 <<"| \n";
        std::cout << std::string(149, '-') << std::endl;
    }
    void display_playlist_with_surah()
    {
        if(!get_Size())
        {
            cout<<"there are no surahs in the playlist to display.....\n";
            return;
        }
        surahs_header();
        for(size_t i = 0; i<get_Size(); ++i)
        {
            surahs[i].print_surah_line(i+1,surahs[i]);
        }
        std::cout << std::string(149, '-') << std::endl;
    }
    void add_surah(const Surah& surah)
    {
        surahs.insert_end(surah);
    }
    void del_surah(const Surah & surah)
    {
        surahs.delete_node_with_key(surah);
    }
    void update_surah(size_t pos, const Surah& surah)
    {
        surahs.update_node_pos(pos, surah);
    }
    void read_playlist()
    {
        cout << "Enter playlist name : ";
        cin >> name;
    }
    Surah & find_surah_by_index(size_t index)
    {
        assert(index>=0 && index<get_Size());
        return surahs[index];
    }
    Surah* find_surah_by_name(const string& sname)
    {
        for (size_t i = 0; i < surahs.get_length(); ++i)
        {
            if (surahs[i].get_name() == sname)
            {
                return &surahs[i];
            }
        }
        return nullptr;
    }
    size_t get_Size()
    {
        return surahs.get_length();
    }
    ~Playlist() = default;
};
class Playlist_Manager
{
private:
    DLL<Playlist> manager;
public:
    Playlist_Manager() {}

    void add_playlist(Playlist & playlist)
    {
        manager.insert_end(playlist);
    }
    void del_playlist(Playlist & playlist)
    {
        manager.delete_node_with_key(playlist);
    }
    Playlist* find_playlist_by_name(const string& playlist_name)
    {
        for (size_t i = 0; i < manager.get_length(); ++i)
        {
            if (manager[i].get_name() == playlist_name)
            {
                return &manager[i];
            }
        }
        return nullptr;
    }
    void print_playlist_header()
    {
        std::cout << std::string(45, '-') << std::endl;
        std::cout<<std::left
                 <<"| "<<std::setw(10)<<"ID"
                 <<"| "<<std::setw(30)<<"playlist Name"
                 <<"| \n";
        std::cout << std::string(45, '-') << std::endl;
    }
    void display_all()
    {
        if(!getSize())
        {
            cout<<"there are no playlists to display.....\n";
            return;
        }
        print_playlist_header();
        for(size_t i = 0; i<getSize(); ++i)
        {
            manager[i].print_line(i+1,manager[i]);
        }
        std::cout << std::string(45, '-') << std::endl;
    }
    size_t getSize()
    {
        return manager.get_length();
    }
    void print_all_playlists_surahs()
    {
        for(int i = 0; i<getSize(); ++i)
        {
            cout<<"--->"<<manager[i].get_name()<<"<---\n";
            manager[i].display_playlist_with_surah();
        }
    }
    void print_specific_playlist_surahs(const string & pname)
    {
        Playlist *p = find_playlist_by_name(pname);
        if (!p)
        {
            cout << "Playlist with the name \"" << pname << "\" not found.\n";
            return;
        }
        cout<<"--->"<<p->get_name()<<"<---\n";
        p->display_playlist_with_surah();
    }
    void update_surah_pos(size_t &pos,string &sname,string &pname)
    {
        Playlist *p = find_playlist_by_name(pname);
        if (!p)
        {
            cout << "Playlist " << pname << " not found.\n";
            return;
        }
        Surah* surah = p->find_surah_by_name(sname);
        if (!surah)
        {
            cout << "Surah " << sname << " not found in Playlist " << pname << ".\n";
            return;
        }
        cout << "Attempting to move Surah --> (" << sname
             << ")<-- in Playlist -->(" << pname << ")<-- to position " << pos << ".\n";
        p->update_surah(pos,*surah);
    }
    void save_playlist_to_file(const string& playlist_name)
    {
        Playlist* playlist = find_playlist_by_name(playlist_name);
        if (!playlist)
        {
            cout << "Playlist not found!\n";
            return;
        }

        string filePath = playlist_name + ".txt";
        ofstream outFile(filePath);

        if (!outFile.is_open())
        {
            cout << "Error opening file for saving.\n";
            return;
        }

        outFile << "Playlist Name: " << playlist->get_name() << "\n";
        outFile << std::string(149, '-') << "\n";
        outFile << std::left
                << "| " << std::setw(10) << "ID"
                << "| " << std::setw(30) << "Surah Name"
                << "| " << std::setw(20) << "Surah Type"
                << "| " << std::setw(80) << "Path"
                << "| \n";
        outFile << std::string(149, '-') << "\n";

        for (size_t i = 0; i < playlist->get_Size(); ++i)
        {
            Surah surah = playlist->find_surah_by_index(i);
            outFile << std::left
                    << "| " << std::setw(10) << (i + 1)
                    << "| " << std::setw(30) << surah.get_name()
                    << "| " << std::setw(20) << surah.get_surah_type()
                    << "| " << std::setw(80) << surah.getAudioFile()
                    << "| \n";
        }

        outFile << std::string(149, '-') << "\n";
        outFile.close();

        cout << "Playlist \"" << playlist_name << "\" saved successfully to " << filePath << "\n";
    }
    void load_playlists_from_file(const string& filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "Error: Unable to open file " << filename << "\n";
            return;
        }

        string line;
        Playlist* currentPlaylist = nullptr;

        while (getline(file, line))
        {
            if (line == "END")
            {
                // End of the current playlist, move to the next
                if (currentPlaylist)
                {
                    add_playlist(*currentPlaylist);
                    delete currentPlaylist;
                    currentPlaylist = nullptr;
                }
            }
            else if (line.find('|') == std::string::npos)
            {
                currentPlaylist = new Playlist(line);
            }
            else
            {
                // Surah line: Parse and add to the current playlist
                if (currentPlaylist)
                {
                    istringstream ss(line);
                    string surahName, surahType, audioFile;
                    getline(ss, surahName, '|');
                    getline(ss, surahType, '|');
                    getline(ss, audioFile, '|');

                    Surah surah(surahName, audioFile, surahType);
                    currentPlaylist->add_surah(surah);
                }
            }
        }
        file.close();
        std::cout << "Playlists successfully loaded from " << filename << "\n";
    }
    ~Playlist_Manager() = default;

};

int main()
{
    int key;
    Playlist_Manager pm;
    do
    {
        system("cls");
        cout<< "\t\t\t\t\t+======================================================+\n"
            << "\t\t\t\t\t|                Quraan Playlist Manager Menu         |\n"
            << "\t\t\t\t\t+======================================================+\n"
            << "\t\t\t\t\t| 1. Add a new playlist                               |\n"
            << "\t\t\t\t\t| 2. Add Shurah to an existing playlist               |\n"
            << "\t\t\t\t\t| 3. Remove Shurah from an existing playlist          |\n"
            << "\t\t\t\t\t| 4. Update the order of existing playlist            |\n"
            << "\t\t\t\t\t| 5. Display All Current Playlists                    |\n"
            << "\t\t\t\t\t| 6. Display all Playlists Shurahs                    |\n"
            << "\t\t\t\t\t| 7. Display Shurahs in a specific playlist           |\n"
            << "\t\t\t\t\t| 8. Play Shurah from specific playlist               |\n"
            << "\t\t\t\t\t|    Use left arrow (<-) to play the previous shurah  |\n"
            << "\t\t\t\t\t|    Use right arrow (->) to play the next shurah     |\n"
            << "\t\t\t\t\t|    Use up arrow (^) to pause the current shurah     |\n"
            << "\t\t\t\t\t|    Use down arrow (v) to resume the current shurah  |\n"
            << "\t\t\t\t\t|    Press q to exit current playlist & return to menu|\n"
            << "\t\t\t\t\t| 9. Save an existing playlist to a file              |\n"
            << "\t\t\t\t\t| 10. Load an existing playlist from a file           |\n"
            << "\t\t\t\t\t| 11. Remove an existing playlist                     |\n"
            << "\t\t\t\t\t| 12. Exit                                            |\n"
            << "\t\t\t\t\t+======================================================+\n"
            << "\t\t\t\t\tYour choice: ";
        cin >> key;
        system("cls");


        if(key == 1 )
        {
            Playlist P;
            P.read_playlist();
            pm.add_playlist(P);
        }
        else if(key == 2)
        {
            if (pm.getSize() == 0)
            {
                cout << "No playlists available.\n";
                break;
            }
            pm.display_all();

            string playlist_name;
            cout << "Enter the name of the playlist you want to add a Surah to: ";
            cin>> playlist_name;

            Playlist* playlist = pm.find_playlist_by_name(playlist_name);
            if (!playlist)
            {
                cout << "Playlist not found!\n";
                break;
            }

            Surah surah;
            surah.read_surah();
            playlist->add_surah(surah);

            char c = 'y';
            while (c == 'y')
            {
                cout << "Add another surah to the current list? (y/n): ";
                cin >> c;
                if (c != 'y') break;

                surah.read_surah();
                playlist->add_surah(surah);
            }
        }
        else if(key == 3)
        {
            string pname,sname;
            pm.display_all();
            cout<<"Enter Playlist name : ";
            cin >> pname;
            cout<<"Enter Surah name : ";
            cin >> sname;
            Playlist *p =  pm.find_playlist_by_name(pname);
            Surah *s = p->find_surah_by_name(sname);
            p->del_surah(*s);
            cout<<sname <<" removed successfully from "<<pname<<"\n";
        }
        else if(key == 4)
        {
            pm.display_all();
            if(!pm.getSize())
                break;
            string pname,sname;
            size_t newPos;
            cout<<"Enter playlist name --> ";
            cin >> pname;
            pm.print_specific_playlist_surahs(pname);
            cout<<"Enter surah name --> ";
            cin >> sname;
            cout<<"Enter new position --> ";
            cin >> newPos;
            pm.update_surah_pos(newPos,sname,pname);
        }
        else if(key == 5)
        {
            pm.display_all();
        }
        else if(key == 6)
        {
            pm.print_all_playlists_surahs();
        }
        else if(key == 7)
        {
            if (pm.getSize() == 0)
            {
                cout << "No playlists available.\n";
                break;
            }
            string playlist_name;
            cout << "Enter the name of the playlist you wanna display its surahs \x02 ";
            cin>> playlist_name;
            pm.print_specific_playlist_surahs(playlist_name);
        }
        else if (key == 8)
        {
            if (pm.getSize() == 0)
            {
                cout << "No playlists available to play.\n";
                cout << "Press Enter to return to the menu...";
                cin.ignore();
                cin.get();
                continue;
            }

            pm.display_all();
            string playlist_name;
            cout << "Enter the name of the playlist you want to play: ";
            cin >> playlist_name;

            Playlist* playlist = pm.find_playlist_by_name(playlist_name);
            if (!playlist || playlist->get_Size() == 0)
            {
                cout << "Playlist \"" << playlist_name << "\" is empty or does not exist.\n";
                cout << "Press Enter to return to the menu...";
                cin.ignore();
                cin.get();
                continue;
            }

            size_t currentIndex = 0;
            sf::Music music;
            bool exitPlaylist = false;

            while (!exitPlaylist)
            {
                Surah& currentSurah = playlist->find_surah_by_index(currentIndex);
                cout << "\nNow playing: " << currentSurah.get_name()<< "\n";
                if (!music.openFromFile(currentSurah.getAudioFile()))
                {
                    cout << "Failed to open file: " << currentSurah.getAudioFile() << "\n";
                    break;
                }

                music.play();
                cout << "Controls(>-<)\n"
                     << "   <-: Previous Surah\n"
                     << "   ->: Next Surah\n"
                     << "   ^ : Pause\n"
                     << "   v : Resume\n"
                     << "   q : Quit Playlist\n";

                while (true)
                {
                    if (_kbhit())
                    {
                        char c = _getch();
                        if (c == 75) // Left Arrow
                        {
                            if (currentIndex > 0)
                            {
                                music.stop();
                                currentIndex--;
                                break;
                            }
                            else
                            {
                                cout << "Already at the first Surah.\n";
                            }
                        }
                        else if (c == 77) // Right Arrow
                        {
                            if (currentIndex < playlist->get_Size() - 1)
                            {
                                music.stop();
                                currentIndex++;
                                break;
                            }
                            else
                            {
                                cout << "Already at the last Surah.\n";
                            }
                        }
                        else if (c == 72) // Up Arrow
                        {
                            music.pause();
                            cout << "Paused.\n";
                        }
                        else if (c == 80) // Down Arrow
                        {
                            music.play();
                            cout << "Resumed.\n";
                        }
                        else if (c == 'q' || c == 'Q') // Quit
                        {
                            music.stop();
                            exitPlaylist = true;
                            break;
                        }
                    }
                }
            }
        }
        else if(key == 9)
        {
            if (pm.getSize() == 0)
            {
                cout << "No playlists available to save.\n";
                break;
            }

            string pname;
            pm.display_all();
            cout << "Enter the name of the playlist you want to save: ";
            cin >> pname;

            pm.save_playlist_to_file(pname);
        }
        else if(key == 10)
        {
            pm.load_playlists_from_file("D:\\DS projects\\playlist_manager\\playlist manager\\playlists.txt");
        }
        else if(key == 11)
        {
            string pname;
            pm.display_all();
            if(!pm.getSize())
            {
                cout << "Press Enter to return to the menu...";
                cin.ignore();
                cin.get();
                break;
            }
            cout<<"Enter Playlist name : ";
            cin >> pname;
            Playlist *p = pm.find_playlist_by_name(pname);
            pm.del_playlist(*p);
            cout<<pname <<" removed successfully \n";
        }
        cout << "Press Enter to return to the menu...";
        cin.ignore();
        cin.get();
    }
    while (key != 12);
    return 0;
}
