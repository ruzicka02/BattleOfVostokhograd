//
// Created by simon on 2.5.22.
//

CShop shop;
ifstream input( "examples/decks/start_hand.csv" );
shop.load_deck(input, true);
input.close();

CDeck deck;
input.open( "examples/decks/start_hand.csv" );
deck.load_deck(input, true);
input.close();

auto g1 = make_shared<CCardGeneral>("General 1", "This general is the best general in the world", 50, 2, 3, 4, 1, null);
auto p1 = CPlayerHuman(g1, deck, &init_screen, &shop);

deck.shuffle_cards();
auto g2 = make_shared<CCardGeneral>("General 2", "This general is also the best general in the world", 50, 2, 3, 4, 1, null);
auto p2 = CPlayerHuman(g2, deck, &init_screen, &shop);

p1.draw_cards(6);

p2.draw_cards(7);
p2.deploy_card(p2.get_hand().at(0));
p2.deploy_card(p2.get_hand().at(0));
p2.deploy_card(p2.get_hand().at(0));

init_screen.context_bar("Game board showcase - deploy cards");

init_screen.refresh_board(&p1, &p2, &shop);
getch();
p1.deploy_card(p1.get_hand().at(2));
init_screen.refresh_board(&p1, &p2, &shop);
getch();
p1.deploy_card(p1.get_hand().at(1));
init_screen.refresh_board(&p1, &p2, &shop);
getch();
p1.deploy_card(p1.get_hand().at(1));
init_screen.refresh_board(&p1, &p2, &shop);
getch();
p1.deploy_card(p1.get_hand().at(1));
init_screen.refresh_board(&p1, &p2, &shop);
getch();