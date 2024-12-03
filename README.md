# ShopSphere

## Descriere proiect

ShopSphere este o aplicație simplă și eficientă pentru gestionarea unui magazin online, care oferă o platformă ușor de utilizat atât pentru administratori, cât și pentru clienți. Aplicația este structurată pe mai multe module, fiecare având o funcționalitate bine definită, contribuind la crearea unei experiențe fluente în administrarea magazinului și efectuarea de tranzacții. Iată principalele componente ale aplicației:

### 1. **Produse**
   - **Clasa `Product`**: Reprezintă produsele din magazin. Fiecare produs conține informații precum numele, descrierea, prețul și un identificator unic (ID). Această clasă permite adăugarea de produse noi în sistem, actualizarea detaliilor acestora și afișarea lor într-o interfață prietenoasă.
   - Exista si clasele `Book`, `Clothing`, `Electronics`, `Furniture`, `Sports` care mostenesc clasa de baza `Product` si adauga atribute speciale.
   
   Produsele pot fi adăugate în coșurile de cumpărături sau în listele de dorințe ale utilizatorilor și sunt folosite pentru a crea comenzile plasate de clienți.

### 2. **Clienți**
   - **Clasa `User`**: Gestionează informațiile utilizatorilor (clienților magazinului). Fiecare utilizator are un ID unic, un nume, un email, o parolă (criptată pentru securitate), o adresă de livrare și un număr de telefon. De asemenea, clienții au un coș de cumpărături și o listă de dorințe, pe care le pot gestiona pe parcursul sesiunii lor.
   - **Gestionarea profilului utilizatorului**: Utilizatorii pot actualiza detaliile personale (nume, email, adresă, număr de telefon) și pot schimba parola. Aceste informații sunt salvate într-un fișier pentru a fi accesibile la logările ulterioare.

### 3. **Coșuri de cumpărături și dorințe**
   - **Clasa `BaseCart`**: Reprezintă coșul de cumpărături de bază, care poate conține mai multe produse, fiecare cu o cantitate specificată. Coșul include funcționalități de adăugare, eliminare și listare a produselor, calcularea prețului total și actualizarea datelor de la fiecare adăugare sau eliminare de produs.
   - **Clasa `ShoppingCart`**: O clasă derivată din `BaseCart`, care permite aplicarea unor reduceri la totalul coșului. Reducerea este opțională și se poate aplica în funcție de preferințele utilizatorului. Prețul total al coșului ține cont de discount, dacă este activat.
   - **Clasa `WishlistCart`**: Permite utilizatorilor să adauge produse dorite în lista lor de dorințe. Aceste produse nu sunt cumpărate imediat, dar pot fi adăugate în coșul de cumpărături atunci când utilizatorul decide să le cumpere.

### 4. **Comenzi**
   - **Clasa `Order`**: Reprezintă o comandă plasată de un client. O comandă conține informații despre utilizator, produsele comandate, cantitățile acestora și statusul comenzii (de exemplu, „În așteptare”, „Plătită”, „Livrată” etc.). De asemenea, fiecare comandă include informații despre metoda de plată aleasă și se poate actualiza pe parcursul procesului de cumpărare.
   - **Funcționalități de gestionare a comenzilor**: Utilizatorii pot urmări starea comenzilor lor, pot solicita rambursări sau pot modifica anumite detalii ale comenzilor plasate (în funcție de statusul acestora).

### 5. **Plăți**
   - **Clasa `Payment`**: O clasă abstractă pentru gestionarea diverselor metode de plată. Acesta definește interfața pentru metodele de plată, inclusiv funcționalitățile de plată și rambursare.
   - **Clasele `CardPayment`, `OnlinePayment` și `CashPayment`**: Sunt clase derivate din `Payment` și implementează metode specifice pentru plata cu cardul, online și în numerar. Fiecare metodă de plată oferă funcționalități personalizate, de exemplu, în cazul plății cu cardul, se efectuează verificarea soldului disponibil și se procesează tranzacția.
   - **Gestionarea erorilor de plată**: În cazul în care există fonduri insuficiente sau alte probleme legate de procesarea plății, aplicația va lansa excepții corespunzătoare (de exemplu, `InsufficientFundsException`).

### 6. **Excepții**
   - **Excepția `InsufficientFundsException`**: Aruncată atunci când un client încearcă să plătească o sumă mai mare decât soldul disponibil, asigurând astfel securitatea și integritatea tranzacțiilor efectuate prin aplicație.

### 7. **Interfață utilizator**
   - **Interfață simplă și intuitivă**: Aplicația oferă o interfață de utilizator clară, unde clienții pot naviga cu ușurință prin produsele disponibile, pot adăuga produse în coș, pot vizualiza totalul coșului de cumpărături și pot finaliza comenzile. De asemenea, utilizatorii pot vizualiza istoricul comenzilor și pot accesa lista de dorințe.
   - **Funcționalități suplimentare**: Utilizatorii pot modifica detaliile personale, pot aplica reduceri la coșul lor și pot alege diverse metode de plată pentru a finaliza comanda.

### 8. **Scopul aplicației**
ShopSphere își propune să ofere o platformă robustă și ușor de utilizat pentru administrarea unui magazin online, fiind un instrument eficient pentru gestionarea produselor, comenzilor, plăților și datelor clienților. Aplicația este scalabilă, astfel încât poate fi extinsă cu ușurință pentru a adăuga noi funcționalități, cum ar fi gestionarea stocurilor, integrări cu platforme de livrare și multe altele.

Aplicația urmărește să faciliteze atât administrarea magazinului, cât și experiența clienților, oferind o soluție simplă și intuitivă pentru cumpărături online.

## Milestone #0

- [x]  Nume proiect (poate fi schimbat ulterior)
- [x] Scurtă descriere a temei alese, ce v-ați propus să implementați

## Milestone #1

#### Cerințe
- [x] definirea a minim **3-4 clase** folosind compunere cu clasele definite de voi
- [x] constructori de inițializare cu parametri
- [x] pentru o aceeași (singură) clasă: constructor de copiere, `operator=` de copiere, destructor
- [x] `operator<<` pentru toate clasele pentru afișare (std::ostream)
- [x] cât mai multe `const` (unde este cazul)
- [x] implementarea a minim 3 funcții membru publice pentru funcționalități specifice temei alese, dintre care cel puțin 1-2 funcții mai complexe
  - nu doar citiri/afișări sau adăugat/șters elemente într-un/dintr-un vector
- [x] scenariu de utilizare a claselor definite:
  - preferabil sub formă de teste unitare, mai ales dacă vorbim de aplicații consolă 
  - crearea de obiecte și apelarea tuturor funcțiilor membru publice în main
  - vor fi adăugate în fișierul `tastatura.txt` DOAR exemple de date de intrare de la tastatură (dacă există); dacă aveți nevoie de date din fișiere, creați alte fișiere separat
- [x] tag de `git`: de exemplu `v0.1`
- [x] serviciu de integrare continuă (CI); exemplu: GitHub Actions

## Milestone #2

#### Cerințe
- [x] separarea codului din clase în `.h` (sau `.hpp`) și `.cpp`
- [x] moșteniri:
  - minim o clasă de bază și **3 clase derivate** din aceeași ierarhie
  - ierarhia trebuie să fie cu bază proprie, nu derivată dintr-o clasă predefinită
  - [x] funcții virtuale (pure) apelate prin pointeri de bază din clasa care conține atributul de tip pointer de bază
    - minim o funcție virtuală va fi **specifică temei** (e.g. nu simple citiri/afișări)
    - constructori virtuali (clone): sunt necesari, dar nu se consideră funcții specifice temei
    - afișare virtuală, interfață non-virtuală
  - [x] apelarea constructorului din clasa de bază din constructori din derivate
  - [x] clasă cu atribut de tip pointer la o clasă de bază cu derivate; aici apelați funcțiile virtuale prin pointer de bază, eventual prin interfața non-virtuală din bază
    - [x] suprascris cc/op= pentru copieri/atribuiri corecte, copy and swap
    - [x] `dynamic_cast`/`std::dynamic_pointer_cast` pentru downcast cu sens
    - [x] smart pointers (recomandat, opțional)
- [x] excepții
  - [x] ierarhie proprie cu baza `std::exception` sau derivată din `std::exception`; minim **3** clase pentru erori specifice
  - [x] utilizare cu sens: de exemplu, `throw` în constructor (sau funcție care întoarce un obiect), `try`/`catch` în `main`
  - această ierarhie va fi complet independentă de ierarhia cu funcții virtuale
- [x] funcții și atribute `static`
- [x] STL
- [x] cât mai multe `const`
- [x] funcții *de nivel înalt*, de eliminat cât mai mulți getters/setters/funcții low-level
- [x] tag de `git`: de exemplu `v0.2`

## Milestone #3

#### Cerințe
- [ ] 2 șabloane de proiectare (design patterns)
- [ ] o clasă șablon cu sens; minim **2 instanțieri**
  - [ ] preferabil și o funcție șablon (template) cu sens; minim 2 instanțieri
- [ ] tag de `git`: de exemplu `v0.3` sau `v1.0`

## Resurse
- adăugați trimiteri către resursele externe care v-au ajutat sau pe care le-ați folosit
