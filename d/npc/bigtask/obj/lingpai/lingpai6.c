
inherit ITEM;

void create()
{
  	set_name("枯松涧火云洞令牌", ({"ling pai", "lingpai", "pai"}));
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
