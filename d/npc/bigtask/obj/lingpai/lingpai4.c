
inherit ITEM;

void create()
{
  	set_name("东海碧波龙宫令牌", ({"ling pai", "lingpai", "pai"}));
  	set_weight(1000);
  	if( clonep() )
    		set_default_object(__FILE__);
  	else 
  	{
    	set("unit", "面");
        set("material", "gold");
    	set("value", 0);
  	}
}
