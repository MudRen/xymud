//Cracked by Roath
inherit ITEM;
inherit F_FOOD;

string *names = ({
  "[33mθθθ[m",
  "[31mι¦ηθ[m",
  "[32mθθθ[m",
  "[33mηηΈθ[m",
  "[34mεθ[m",
  "[35mιΉΏθ[m",
});

string *ids = ({
    "laohu rou",
    "xiangzhang rou",
    "mangshe rou",
    "huli rou",
    "tu rou",
    "lu rou",
});

void create()
{
  int i = random(sizeof(names));
  set_name(names[i], ({ids[i]}));
  set_weight(80);
      if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "δΈεΏ«ι¦ε·ε·ηηθγ\n");
                set("unit", "ε");
                set("value", 100);
                set("food_remaining", 3);
                set("food_supply", 30);
        }
}

