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

Obsahem semestrální práce je engine pro hraní karetního RPG pro 2 hráče z vojenského prostředí. Generálové soupeřících vojsk budou v rekrutovacím táboře nakupovat nové karty, aby mohli zneškodnit svůj protějšek a tím obsadit sporné město Vostokhograd, ležící kdesi na východ od nás. Hra je realizována v grafickém terminálovém prostředí ncurses.

Na začátku hry má každý hráč svou vlastní kartu generála (které se mohou lišit počtem životů, pasivními schopnostmi) a balíček několika startovních karet. Zároveň se na hrací ploše nachází rekrutovací tábor s lepšími kartami, které si hráči mohou v průběhu hry za hřivny kupovat. V táboře je viditelných jen několik karet, které se postupně s nákupy hráčů doplňují. Hra končí v okamžiku, kdy počet životů jednoho z generálů klesne na nulu.

Průběh hry: V každém kole si generál lízne několik karet ze svého balíčku, rozdělené na jednorázové (Warcry) a trvalé (Troop). Všechny karty může a musí zahrát hned v tomto tahu. Hráč může nakoupit nové karty z tábora do svého odhazovacího balíčku, tyto karty si později bude moci líznout v následujících tazích. Hráč může použít body útoku na nepřátelské jednotky a body obrany na doplnění životů svých jednotek (včetně generálů). Pokud hráč zneškodní soupeřovu jednotku, doplní se jí všechny životy a vrátí se do soupeřova odhazovacího balíčku. Na konci tahu odhodí jednorázové karty do svého odhazovacího balíčku, trvalé karty zůstávají před ním.

Implementace varianty pro dva hráče bude zjednodušená tím, že karty není třeba skrývat, soupeř musí ve svém tahu vše zahrát. Hráči se budou po jednom kole hry střídat. Samozřejmě bude implementována i varianta pro jednoho hráče proti "umělé inteligenci". Hypotetickým, avšak implementovatelným návrhem by pak byla hra pro ještě vyšší počet hráčů (ta by však byla u jednoho zařízení obtížně hratelná).

Ukládání a načítání rozehrané hry bude probíhat ve formě zapsání (resp. čtení) stavu hry do souboru "balíčků" + vyložených karet s pozměněnými životy. Ukládají se karty v ruce hráče/AI, jejich lízací/odhazovací balíčky a stav rekrutovacího tábora. Stejnou formou proběhne i načtení definic všech dostupných karet při spuštění hry.

## Návrh tříd

Hojně používanou třídou ve hře bude jedna karta (**CCard**), která bude i základem hlavního polymorfismu - dědit z ní budou třídy **CCardWarcry**, **CCardTroop**, **CCardGeneral**. Všechny karty bude možné umístit do balíčku karet, který bude reprezentovat třída **CDeck**. Za balíček karet se bude považovat libovolná kolekce, jako například karty v ruce. Speciálním případem jsou karty dostupné v rekrutovacím táboře, které reprezentuje třída **CShop**.

Všechny karty budou ukládat efekty svých akcí, jako je síla útoku (Damage), síla obrany (Protection) nebo kupní síla (₴, hřivny) v číselné podobě (pokud tuto vlastnost karta nemá, bude uložena hodnota 0). Speciální schopnosti (např. lízni si kartu, seber soupeřovu jednotku) se budou ukládat jako hodnota typu enum.

Abstraktní třída **CPlayer** bude následně obalovat hráčského generála a čtyři balíčky (lízací balíček, karty v ruce, vyložené karty, odhazovací balíček) a bude zajišťovat operace mezi nimi (lízni si N karet, odhoď zbylé karty, vylož trvalou jednotku, ...). Tato třída bude také poskytovat rozhraní pro útoky na karty protějšího hráče. Z této třídy budou následně dědit **CPlayerHuman** (ovládaná hráčem) a **CPlayerAI** (ovládaná počítačem).

Všechny zmíněné herní aspekty bude obalovat třída **CGame**. Ta bude řídit logiku jednotlivého průběhu hry (střídání tahů hráčů, příprava na začátku/konci hry) a předávat informace k vykreslení na terminál. O vykreslování samotné se pak bude starat třída **CDisplay**.

## Polymorfismus

- Typy karet: jednorázové (Warcry), trvalé (Troop), hráčská postava (General)
- Ovládání hráče: lokální hráč, umělá inteligence (různé druhy)

## Zdroje

Inspirací pro semestrální práci byla karetní hra Hero Realms (https://www.herorealms.com/).
