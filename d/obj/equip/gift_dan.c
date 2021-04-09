#include <ansi.h>
inherit COMBINED_ITEM;

nosave string *index=({
	"str","con","int","spi","cps","per","cor","kar",
});

nosave mapping giftn=([
	"str":"体格", "con":"根骨", "int":"悟性", "spi":"灵性",
	"cps":"定力", "per":"容貌", "cor":"胆识", "kar":"福缘",
]);

nosave mapping gift=([]);

int query_autoload(){return 1;}

void setup(){}
void do_finish(object);
void get_finish(string, object);
void get_input2(string, object);
void get_input(string, object);
void show_gift(object);

void create()
{
	set_name("天赋丹",({"tianfu dan","gift drug","dan"}));
	if(clonep()) 
		set_default_object(__FILE__); 
	set("base_unit", "颗");
	set("unit","些");
	set("long","一颗充满了神奇的丹药，据说用它可以调节自身的先天属性。(tiaojie)\n");
	set("value",999990000);
	set("no_put",1);
	set("no_sell",1);
	set("no_give",1);
	set("level",1);
	setup();
	set_amount(1);
}

void init()
{
	object me = this_player();
	if( userp(me) && present(this_object(),me) )
		add_action("do_tiaojie","tiaojie");
}

void do_finish(object me)
{
	int i;
	string *args;
	mapping my,data;
	if( !me )
		return;
	my = me->query_temp("gift_dan");	
	if( !my || !mapp(my) )
		return;
	data = me->query_entire_dbase();
	for(i=0;i<sizeof(index);i++)
		data[index[i]] = my[index[i]];
	me->delete_temp("gift_dan");
	me->save();
	message("channel:rumor",HIM"【"HIY"天赋调整"HIM"】某人：听说"HIC+me->query("name")+HIM"使用"HIY"天赋丹"HIM"调整了自己的先天天赋。\n"NOR,users());
	if( query_amount()>1 )
		this_object()->add_amount(-1);
	else
		destruct(this_object());
}		

void get_finish(string arg, object me)
{
	if(!me) return;
    if(!arg) 
    {
		write("你确定接受当前的天赋设置吗？[y/n]");
		input_to("get_finish",me);
		return;
	}
    if(arg[0..0]=="y" || arg[0..0]=="Y") 
    {
		do_finish(me);
		return;
    }
    if(arg[0..0]=="n" || arg[0..0]=="N") 
    {
    	me->delete_temp("gift_dan");
		show_gift(me);
		write("你要降低哪个天赋？[0-7]：");
		input_to("get_input",me);
		return;
    }
    write("你确定接受当前的天赋设置吗？[y/n]");
    input_to("get_finish",me);
    return;
}

void get_input2(string arg, object me)
{
	int v,ind;
	mapping my;

    if(!me) return;
	v = query("level");
	if( v<1 ) v  = 1;
	if( v>20 ) v = 20;

	if( !arg || sscanf(arg,"%d",ind)!=1 
	 || (ind<0 && ind>7) ) 
	{
		show_gift(me);
		write("你要将多出来的天赋点增加到哪个天赋？[0-7]：");
		input_to("get_input2",me);
		return;
	}
    my = me->query_temp("gift_dan");
    if(!my || !mapp(my)) 
    {
		write("有出错，冇问题.\n");
		return;
    }
    if( my[index[ind]]>=100 )
    {
    	write("你的"+giftn[index[ind]]+"已经很高了。\n");
		show_gift(me);
		write("你要将多出来的天赋点增加到哪个天赋？[0-7]：");
		input_to("get_input2",me);
    	return;
    } 
	write("你决定将"+giftn[index[ind]]+"提高"HIR+v+NOR"点。\n");
	my[index[ind]] = (int)my[index[ind]]+v;
	show_gift(me);
	write("你确定接受当前的天赋设置吗？[y/n]");
    input_to("get_finish",me);
	return;
}

void get_input(string arg, object me)
{
	int v,ind;	
	mapping my;

    if(!me) return;
	v = query("level");
	if( v<1 ) v  = 1;
	if( v>20 ) v = 20;
	if( !arg || sscanf(arg,"%d",ind)!=1 
	 || (ind<0 && ind>7) ) 
	{
		show_gift(me);
		write("你要降低哪个天赋？[0-7]：");
		input_to("get_input",me);
		return;
	}
    my = me->query_temp("gift_dan");
    if(!my || !mapp(my)) 
    {
		write("有出错，冇问题.\n");
		return;
    }
    if( my[index[ind]]<=10 )
    {
    	write("你的"+giftn[index[ind]]+"已经很低了。\n");
		show_gift(me);
		write("你要降低哪个天赋？[0-7]：");
		input_to("get_input",me);
    	return;
    } 
	write("你决定将"+giftn[index[ind]]+"降低"HIR+v+NOR"点。\n");
	my[index[ind]] = (int)my[index[ind]]-v;
	show_gift(me);
	write("你要将多出来的天赋点增加到哪个天赋？[0-7]：");
	input_to("get_input2",me);
}

void show_gift(object who)
{
	string str,*args;
	int i;
	mapping my;
	if( !who )
		return;
	my = who->query_temp("gift_dan");
	if( !my || !mapp(my) )		
		my = who->query_entire_dbase();
	if( !my || !mapp(my) )
	{
		write("你先天不全。\n");
		return;
	}
	
	gift = ([]);
	for(i=0;i<sizeof(index);i++)
		gift[index[i]] = my[index[i]];
	
	who->set_temp("gift_dan",gift);	
	
	str = "你的先天属性如下：\n";
	str+= sprintf(
	    " 0. 体格：[%d]        1. 根骨：[%d]\n"+
	    " 2. 悟性：[%d]        3. 灵性：[%d]\n"+
	    " 4. 定力：[%d]        5. 容貌：[%d]\n"+	    
        " 6. 胆识：[%d]        7. 福缘：[%d]\n",
	    my["str"],my["con"],my["int"],my["spi"],
	    my["cps"],my["per"],my["cor"],my["kar"],	    
	    );
	write(str);
	return;
}

int do_tiaojie()
{
	object me = this_player();
	if( !present(this_object(),me) )
		return 0;
	show_gift(me);
	write("你要降低哪个天赋？[0-7]：");
	input_to("get_input",me);
	return 1;
}
		
string query_title(int v)
{
	if( v<=1 )
		return "凡品";
	else if( v<=3 )	
		return "下品";
	else if( v<=5 )	
		return "中品";
	else if( v<=8 )	
		return "上品";
	else if( v<=10 )	
		return "极品";
	else if( v<=15 )	
		return "仙品";
	else
		return "神级";
}	

string short()
{
	string msg,str = ::short();
	str+= "(御)";
	msg = query_title(query("level"));
	str = replace_string(str,"天赋丹",msg+"天赋丹");
	return str;
}
		