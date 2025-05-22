🔥 Cel: Opanować C++ praktycznie i z sensem, bez przemęczenia
🧱 Etap 1: „Kurde, to działa!” – totalne podstawy w praktyce (1–2 tygodnie)
    Poznaj:

    #include, main(), std::cout, std::cin

    Typy (int, float, string, bool)

    if, switch, while, for

    Funkcje (int dodaj(int a, int b))

    📌 Rób małe programy:

    kalkulator

    zgadnij liczbę

    licznik znaków w tekście



🧱 Etap 2: „To już pachnie prawdziwym kodem” – klasy i obiekty (2–3 tygodnie)
    Poznaj:

    class, public, private

    constructor, this

    prosta klasa User z metodą introduce()

    📌 Zrób projekt:

    system użytkowników (dodaj, wypisz)

    obiekt TestCase z status, nazwa, czas_trwania


🧱 Etap 3: „To się zaczyna przydawać” – kontenery STL + pliki (2–3 tygodnie)
    Poznaj:

    std::vector, std::map, std::string

    for(auto x : wektor)

    fstream – zapis/odczyt do pliku

    📌 Zrób projekt:

    logger do pliku (dodaje timestampy)

    prosty system zapamiętujący historię poleceń


🧱 Etap 4: „Mam narzędzie w ręce” – większy projekt (reszta czasu, bez presji)
    📌 Propozycje projektów (pasujące do CI/robotów/telekomu):

    parser logów testowych (std::ifstream, std::map)

    CLI tool do raportu testów (std::vector<TestResult>)

    system do mierzenia czasu testów i generowania JSON-a (z Boost albo własną klasą)



#Klasy ------------------
ETAP 1: Podstawowa klasa i obiekt
    class, public, private

    tworzenie obiektu (User u1)
    pola (zmienne wewnątrz klasy)

    metoda wewnątrz klasy (u1.print())

    👉 Po co? Żeby wiedzieć jak się tworzy, używa, co widać a co nie

🧱 ETAP 2: Konstruktory
    konstruktor domyślny (User())

    konstruktor z argumentami (User(string, int))

    this-> do rozróżniania zmiennych

    inicjalizacja zmiennych (User(string name): name(name) {})

👉 Po co? Żeby tworzyć obiekty z sensownymi danymi

🧱 ETAP 3: Encapsulacja + gettery/settery
    private dane → public metody dostępu (getName(), setName())

    ochrona danych przed grzebaniem z zewnątrz

    kontrola (np. nie pozwól ustawić wieku < 0)

    👉 Po co? Bezpieczne zarządzanie danymi obiektów

🧱 ETAP 4: Słowo kluczowe const i metody stałe
    metody, które nic nie zmieniają → void print() const

    pola stałe const int id;

    wskaźniki const vs int* const

    👉 Po co? Żeby jasno pokazać co może zmieniać obiekt, a co nie

🧱 ETAP 5: Funkcje i klasy statyczne
    static int counter;

    static void log();

    klasa narzędziowa bez obiektu (Utils::print())

👉 Po co? Gdy coś nie zależy od konkretnego obiektu, tylko od klasy

🧱 ETAP 6: Dziedziczenie
    class B : public A

    nadpisywanie metod (virtual, override)

    wskaźnik do klasy bazowej (A* ptr = new B())

👉 Po co? Żeby mieć wspólny interfejs dla różnych klas (np. TestCase, RetryCase)

🧱 ETAP 7: Operator <<, >> – przeciążenie
    friend std::ostream& operator<<(...)

    friend std::istream& operator>>(...)

    wypisywanie własnych obiektów jak std::cout << myObject

    👉 Po co? Żeby debugować i logować czytelnie

🧱 ETAP 8: Destruktory i zarządzanie pamięcią
    ~User()

    co się dzieje przy delete

    new i delete dla dynamicznych obiektów

👉 Po co? Żeby nie mieć wycieków pamięci

🧱 ETAP 9: Kopiowanie i ruch (copy, move)
    konstruktor kopiujący

    konstruktor przenoszący

    operator przypisania =

    std::move()

    👉 Po co? Żeby mieć kontrolę nad tym co się dzieje przy kopiowaniu i przekazywaniu obiektów

🧱 ETAP 10: Szablony klas (template)
    template<typename T> class Box { ... }

    uniwersalne klasy

    Box<int>, Box<std::string>

    👉 Po co? Żeby pisać kod raz, a używać dla różnych typów

    🧱 ETAP 11: Przyjaźń (friend) i klasy zaprzyjaźnione
    friend funkcja lub klasa może zaglądać do private innej klasy

    👉 Po co? Gdy naprawdę musisz dać dostęp (np. operator <<)

🧱 ETAP 12: Prawdziwy projekt z klasą
    Na koniec:

    mini-projekt z klasą TestCase, TestRun, Logger, Report

    eksport do CSV / JSON

    debug print przez operator<<

    może podpięcie do testów z Robot Frameworka?