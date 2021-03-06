# Battle of Vostokhograd: The Card RPG

## Zadání

Naprogramujte engine pro hraní karetního RPG

Váš engine:

- ze souboru nahraje definici karet (jejich typ, atributy, efekty), balíčku (seznam karet v balíčku)
- umožní vytvořit a hrát samotnou karetní hru
- implementuje variantu pro jednoho hráče proti počítači (náhodné tahy nestačí)
- implementuje variantu pro dva hráče (výměna přes potvrzovací okno, aby soupeř neviděl karty, nebo naopak soupeři si celou dobu do karet vidí)
- umožňuje ukládat a načítat rozehrané hry

Kde lze využít polymorfismus? (doporučené)

- Typy karet: útočné, obranné, speciální, ...
- Efekty akcí: síla útoku, síla obrany, vem si X karet, zahoď X karet
- Ovládání hráče: lokální hráč, umělá inteligence (různé druhy), síťový hráč
- Uživatelské rozhraní: konzole, ncurses, SDL, OpenGL (různé varianty), ...

## Rozšíření

Obsahem semestrální práce je engine pro hraní karetního RPG pro 2 hráče, s ukázkovou karetní hrou z vojenského prostředí. V této hře budou generálové soupeřících vojsk v rekrutovacím táboře nakupovat nové karty, aby mohli zneškodnit svůj protějšek a tím obsadit sporné město Vostokhograd, ležící kdesi na východ od nás. Vykreslování na obrazovku je realizováno pomocí grafické terminálové knihovny ncurses.

Na začátku hry má každý hráč svou vlastní kartu generála (které se mohou lišit počtem životů, pasivními schopnostmi) a balíček několika startovních karet. Zároveň se na hrací ploše nachází obchod s lepšími kartami (rekrutovací tábor), které si hráči mohou v průběhu hry za peníze (hřivny) kupovat. V táboře je viditelných jen několik karet, které se postupně s nákupy hráčů doplňují. Hra končí v okamžiku, kdy počet životů jednoho z generálů klesne na nulu.

Průběh hry: V každém kole si generál lízne několik karet ze svého balíčku, rozdělené na jednorázové (Warcry) a trvalé (Troop). Všechny karty může a musí zahrát hned v tomto tahu. Hráč může nakoupit nové karty z tábora do svého odhazovacího balíčku, tyto karty si později bude moci líznout v následujících tazích. Hráč může použít body útoku na nepřátelské jednotky a body obrany na doplnění životů svých jednotek (včetně generála). Pokud hráč zneškodní soupeřovu jednotku, doplní se jí všechny životy a vrátí se do soupeřova odhazovacího balíčku. Na konci tahu odhodí jednorázové karty do svého odhazovacího balíčku, trvalé karty zůstávají před ním.

Implementace varianty pro dva hráče bude zjednodušená tím, že karty není třeba skrývat, soupeř musí ve svém tahu vše zahrát. Hráči se budou po jednom kole hry střídat. Implementována je i varianta pro jednoho hráče proti "umělé inteligenci". K dispozici je "chytrá" umělá inteligence, posuzující kvalitu/užitečnost karet při jejich hraní/nákupu, ale také umělá inteligence hrající čistě na základě náhodných tahů.

Ukládání a načítání rozehrané hry probíhá ve formě zapsání (resp. čtení) stavu hry do souboru "balíčků". Ukládají se všechny balíčky obou hráčů a stav rekrutovacího tábora. Stejnou formou proběhne i načtení definic všech dostupných karet (rekrutovací tábor, startovní karty v ruce) při spuštění hry.

## Návrh tříd

Hojně používanou třídou ve hře bude jedna karta (**CCard**), ze které následně dědí **CCardGeneral** a **CCardDeckable**. K tomuto rozdělení došlo proto, aby bylo jednoznačně viditelné oddělení třídy generála, která se nechová polymorfně (na hráče se váže právě jeden generál, nemůže se jednat o jiný typ karty), od abstraktní třídy **CCardDeckable**, která bude i základem hlavního polymorfismu - dědit z ní následně budou třídy **CCardWarcry** a **CCardTroop**. Karty dědící z **CCardDeckable** je možné umístit do balíčku karet, který bude reprezentovat třída **CDeck**. Za balíček karet se bude považovat libovolná kolekce, jako například karty v ruce nebo na stole. Speciálním případem jsou karty dostupné v rekrutovacím táboře, které reprezentuje třída **CShop**.

Všechny karty budou ukládat efekty svých akcí, jako je síla útoku (Damage), síla obrany (Protection) nebo kupní síla (₴, hřivny) v číselné podobě (pokud tuto vlastnost karta nemá, bude uložena hodnota 0). Speciální schopnosti (např. lízni si kartu, seber soupeřovu jednotku) se budou ukládat jako hodnota typu **EAbility** (enum).

Abstraktní třída **CPlayer** bude následně obalovat hráčského generála a čtyři balíčky (lízací balíček, karty v ruce, vyložené karty, odhazovací balíček) a bude zajišťovat operace mezi nimi (lízni si N karet, odhoď zbylé karty, vylož trvalou jednotku, ...). Tato třída bude také poskytovat rozhraní pro útoky na karty protějšího hráče. Z této třídy budou následně dědit **CPlayerHuman** (ovládaná hráčem), **CPlayerAI** (ovládaná počítačem) a **CPlayerBogo** (ovládaná počítačem pomocí čistě náhodných tahů).

Všechny zmíněné herní aspekty bude obalovat třída **CGame**. Ta bude řídit logiku jednotlivého průběhu hry, jako je například střídání tahů hráčů, příprava na začátku hry (vytvoření nové hry, načtení uložené pozice) nebo její řádné ukončení. O vykreslování samotné se pak bude starat třída **CDisplay**, jejíž metody jsou volané z různých částí kódu. Jedinou vyjímkou vykreslování na terminál mimo třídu CDisplay je pak metoda CCard::print_card(), která vykreslí jednu kartu (potřebuje přístup ke všem jejím složkám a volá se velmi často).

Diagram návrhu tříd lze vygenerovat z hlavičkových souborů za použití přiloženého Doxyfile.

Ve složce zdrojových souborů se navíc nachází knihovna funkcí **Test.cpp**, která zkouší zobrazit na terminál různé herní scénáře a provádí jednoduché asserty. Funkce z této knihovny se provedou ve funkci main, pokud je program spuštěn s přepínačem `--debug`. Zároveň je program možné spustit s přepínačem `--mem-check`, který spustí různé funkce knihovny ncurses, které po sobě řádně neuklízí paměť. Tato krátká funkce by měla mít stejné množství neuvolněné paměti, jako libovolný průchod hrou samotnou, což ukazuje, že program žádnou paměť nezanechává neuvolněnou vlastní vinou.

## Polymorfismus

- Typy karet v balíčku (CCardDeckable): jednorázové (Warcry), trvalé (Troop)
    - Poznámka: Vztah dědičnosti na CCard (Deckable, General) není polymorfický, kvůli použití CCardGeneral ani nemůže
- Ovládání hráče(CPlayer): lokální hráč (Human), umělá inteligence (AI), náhodné tahy (Bogo)

## Inspirace

Inspirací pro semestrální práci byla karetní hra [Hero Realms](https://www.herorealms.com/). Některé herní mechaniky mohou naopak nápadně připomínat multiplatformní karetní hru v digitální podobě [Hearthstone](https://playhearthstone.com/).

## Případné vylepšení

- Nastavitelné zobrazování karet pomocí UTF-8 (metoda print_card_wide() špatně funguje na terminálech nepodporujících UTF-8 znaky)
- Alternativní zobrazovací rozhraní (např. CLI pro ukázku absence memory leaků)

# Ukázka

[![Video showcase](https://img.youtube.com/vi/jJ5Pid4QQRA/0.jpg)](https://www.youtube.com/watch?v=jJ5Pid4QQRA "Video showcase")