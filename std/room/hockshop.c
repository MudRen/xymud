// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// hockshop.c
// modified by mon 2/28/98
#include "/cmds/std/valid_move.h"
inherit ROOM;

string *sell_msg = ({
     "破破烂烂，一文不值",
     "质地低劣，难看之极",
     "又脏又破，臭气熏天",
});

object shop_box;

int query_max_items() {return 100;}
string get_name(string str);

void init()
{
   add_action("do_value", "value");
   add_action("do_pawn", "pawn");
   add_action("do_sell", "sell");
   add_action("do_retrieve", "retrieve");
   add_action("do_buy", "buy");
   add_action("do_list", "list");
  // add_action("do_quit", "quit");

   set("no_clean_up", 1);
}

// find the shopbox object for this shop to hold sold items.
object findbox()
{
    if(shop_box && environment(shop_box)==this_object()) 
      return shop_box;

    shop_box=new(__DIR__"shopbox");
    shop_box->move(this_object());
    return shop_box;
}

string value_string(int value)
{
	return MONEY_D->money_str(value,1);	
}

void pay_player(object who, int amount)
{
	return MONEY_D->pay_player(who,amount);
}

int do_value(string arg)
{
   	object ob;
   	int value, sale;

   	if( !arg || !(ob = present(arg, this_player())) )
     		return notify_fail("你要拿什么物品给当铺估价？\n");

   	if( ob->query("money_id") )
     		return notify_fail("这是「钱」，你没见过吗？\n");

   	value = ob->query("value");
   	sale=ob->query_temp("sale_price");
   	if(sale>0 && sale<value) value=sale;

   	if( !value) printf("%s一文不值。\n", ob->query("name"));
   	else 
     		printf("%s价值%s。\n如果你要典当(pawn)，可以拿到%s及一张当票。\n如果卖断(sell)，可以拿到%s。\n",
        ob->query("name"), value_string(value),
     value_string(value * 15 / 100), value_string(value * 20 / 100));
	return 1;
}

int do_pawn(string arg)
{
   	object ob, stamp_ob;
   	int value, value1 , sale;
   	string obj_file;
   	int  i;

   	if( this_player()->is_busy() )
     		return notify_fail("你现在正忙着呢。\n");

   	if( arg = this_player()->query_id() )
   	{
	      	value1 = 1 ;
	      	if( !ob = present("sword", this_player()) )
      			return notify_fail("你不能典当这个。\n");
   	}
   	else if( !arg || !(ob = present(arg, this_player())) )
     		return notify_fail("你要典当什么物品？\n");

   	if( ob->query("money_id") )   return notify_fail("你要当「钱」？\n");

        if( ob->query_temp("sale_price") )  return notify_fail("掌柜的说：我们不收购二手物品。\n");
   	if( ob->query("material") == "ice" )
     		return notify_fail("掌柜的说：冰的东西我们这里没法存放。\n");
   //cuz ice melts, will cause problem, so disabled...weiqi, 970930.

   	value = ob->query("value");
   	sale=ob->query_temp("sale_price");
   	if(sale>0 && sale<value) value=sale;

   	if( !value || value < 10) return notify_fail("这样东西不值钱。\n");
        if(ob->query("no_sell"))
      		return notify_fail("这样东西不能买卖。\n");

   	write("掌柜的唱道："+ sell_msg[random(sizeof(sell_msg))] +ob->query("name") + "一" + ob->query("unit") + "，押"+value_string(value*15/100)+ "。\n");
   	message_vision("$N把身上的" + ob->query("name") + "拿出来典当了"+ value_string(value * 15 / 100) + "。\n", this_player());
	value1 ? stamp_ob = new("/obj/npc/obj/stamps") :  stamp_ob = new("/obj/stamps");
	stamp_ob->set_temp("file", ob);
     	stamp_ob->set_temp("value", value*15/100);
   	stamp_ob->set_temp("player", this_player()->query("id"));
   	stamp_ob->set_temp("long_1", this_player()->name()+"典当" +ob->query("name") + "一" + ob->query("unit") +"讫，破烂缺损不堪。");
        stamp_ob->set_temp("long_2", "赎回应付"+value_string(value*70/100)+"整，一手交钱，一手交货。");

   	this_player()->start_busy(1);
     	pay_player(this_player(), value * 15 / 100);
   	stamp_ob->move(this_player());

   //destruct(ob);
	ob->move(findbox());
	return 1;
}

int do_sell(string arg)
{
        object ob;
        int value, sale,sv;
        string obj_file;
        int i, oldnum;
        string index;

        if( this_player()->is_busy() )
                return notify_fail("你现在正忙着呢。\n");

        if( !arg || !(ob = present(arg, this_player())) )
                return notify_fail("你要卖断什么物品？\n");

        if( ob->query("money_id") )   return notify_fail("你要卖「钱」？\n");
        value = ob->query("value");
//        sale=ob->query_temp("sale_price");
        if( ob->query_temp("sale_price") )  return notify_fail("掌柜的说：我们不收购二手物品。\n");
        if(sale>0 && sale<value) value=sale;
        if( !value ) return notify_fail("这样东西不值钱。\n");
        if(ob->query("no_sell"))
                return notify_fail("这样东西不能买卖。\n");

        if( ob->query("material") == "ice" )
                return notify_fail("掌柜的说：冰的东西我们这里没法存放。\n");
   //cuz ice melts, will cause problem, so disabled...weiqi, 970930.
        sv = value*20/100;
        write("掌柜的唱道："+ sell_msg[random(sizeof(sell_msg))] +ob->query("name") + "一" + ob->query("unit") + "，当"+value_string(sv)+ "。\n");
        message_vision("$N把身上的" + ob->query("name") + "卖掉。\n",this_player());

        index=ob->query("name")+"("+ob->query("id")+")";

        if(!findbox()->query_temp("goods/"+index) ){
                findbox()->set_temp("goods/"+index, ob);
                findbox()->set_temp("numbers/"+index, 1);
                ob->move(findbox());
        }
        else 
        {
                oldnum = findbox()->query_temp("numbers/"+index);
                findbox()->set_temp("numbers/"+index, oldnum+1);
                destruct(ob);
        }

        this_player()->start_busy(1);
        pay_player(this_player(), sv);
        return 1;
}

int do_retrieve(string arg)
{
   	object ob;
   	int value, afford;
   	object pawn_ob;

   	if( this_player()->is_busy() )
     		return notify_fail("你现在正忙着呢。\n");

   	if( !arg || !(ob = present(arg, this_player())) )
     		return notify_fail("你要赎回什么物品。\n");

   	if( ob->query("id") != "pawn stamp")
      		return notify_fail("你要用当票才能赎回物品。\n");

   	value = ob->query_temp("value");
   	if(!value) 
      		return notify_fail("用空白当票来赎物，光天化日之下想打劫不成！\n");

   	if( !this_player()->check_pay(value) ) 
		return notify_fail("你没有足够的钱来赎回。\n");
	if( ob->query_temp("player") != this_player()->query("id"))
      		return notify_fail("又不是你当的，想趁火打劫啊！\n");

   	pawn_ob = ob->query_temp("file");
   	if(!pawn_ob) 
   	{
     		destruct(ob);
     		return notify_fail("掌柜的惊道：糟糕！你要的东西找不着了。\n");
        }
	if(!pawn_ob->move(this_player())) return 0;
   	destruct(ob);
	write("掌柜的唱道："+ sell_msg[random(sizeof(sell_msg))] +pawn_ob->query("name") + "一" + pawn_ob->query("unit") + "，赎银"+value_string(value)+ "。\n");
   	message_vision("$N用当票赎回一"+pawn_ob->query("unit")+pawn_ob->query("name")+"。\n", this_player());
	this_player()->start_busy(1);
   	this_player()->pay_money(value);
	return 1;
}

int do_list(string arg)
{
   	mapping goods;
   	string list, *name;
   	int i,turn=0;
   	string tlist;
   	object me=this_player();

   	if( !mapp(goods = findbox()->query_temp("goods")) )
     		return notify_fail("当铺目前没有任何货物可卖。\n");
   	name = keys(goods);
   	if(!sizeof(goods)) 
     		return notify_fail("当铺目前没有任何货物可卖。\n");

   	if( !arg )   
   	{
      		list = "你可以购买下列这些东西：\n";
//      write(list);
      		i=sizeof(goods);
      		while(i--) 
      		{
             		if(!goods[name[i]]) {
          			findbox()->delete_temp("numbers/"+name[i]);
          			findbox()->delete_temp("goods/"+name[i]);
          			continue;
             		}
			tlist = get_name(name[i]);
        		++turn;
        		list += sprintf("%-3d %-30s：%-20s：还剩%s%s\n",turn, tlist,value_string(goods[name[i]]->query("value")),
          					chinese_number(findbox()->query_temp("numbers/"+name[i])),
          					goods[name[i]]->query("unit") );
         
      		}
       		me->start_more(list);
   	}
   	else if( arg == "book" )  
   	{
     		turn=0;
     		list = "";
     		i=sizeof(goods);
     		while(i--) {
             		if(!goods[name[i]]) {
          			findbox()->delete_temp("numbers/"+name[i]);
          			findbox()->delete_temp("goods/"+name[i]);
          			continue;
             		}
			if( mapp(goods[name[i]]->query("skill")) )   {
           			tlist = get_name(name[i]);
           			++turn;
           			list += sprintf("%3d %-30s：%-20s：还剩%s%s\n",turn,tlist,
             					value_string(goods[name[i]]->query("value")),
             					chinese_number(findbox()->query_temp("numbers/"+name[i])),
             					goods[name[i]]->query("unit") );
      			}
     		}
      		if( list == "" )
      			write("当铺目前没有这种货品．\n");
      		else {
   			list = "你可以购买下列这些东西：\n"+list;
   			me->start_more(list);
      		}
   	}
   	else if( arg == "drug" )  {
     		turn=0;
     		list = "";
     		i=sizeof(goods);
     		while(i--) {
             		if(!goods[name[i]]) {
          			findbox()->delete_temp("numbers/"+name[i]);
          			findbox()->delete_temp("goods/"+name[i]);
          			continue;
             		}
      			if( goods[name[i]]->query("drug_type") )   {
      	   			++turn;
           			tlist = get_name(name[i]);
           			list += sprintf("%3d %-30s：%-20s：还剩%s%s\n",turn,tlist,
             			value_string(goods[name[i]]->query("value")),
             			chinese_number(findbox()->query_temp("numbers/"+name[i])),
             			goods[name[i]]->query("unit") );
      			}
     		}
      		if( list == "" )
      			write("当铺目前没有这种货品．\n");
      		else {
   			list = "你可以购买下列这些东西：\n"+list;
   			me->start_more(list);
      		}
   	}
   	else if( arg == "axe" || arg == "blade" || arg == "dagger" || 
   	arg == "fork" || arg == "hammer" || arg == "spear" || arg == "mace" || arg == "rake" ||
   	arg == "staff" || arg == "stick" || arg == "sword" || arg == "whip" ||
   	arg == "throwing" )  {
     		list = "";
     		turn=0;
     		i=sizeof(goods);
     		while(i--) {
             		if(!goods[name[i]]) {
          			findbox()->delete_temp("numbers/"+name[i]);
          			findbox()->delete_temp("goods/"+name[i]);
          			continue;
             		}
			if( goods[name[i]]->query("skill_type") == arg )   {
      	   			++turn;
           			tlist = get_name(name[i]);
           			list += sprintf("%3d %-30s：%-20s：还剩%s%s\n", turn,tlist,
             			value_string(goods[name[i]]->query("value")),
             			chinese_number(findbox()->query_temp("numbers/"+name[i])),
             			goods[name[i]]->query("unit") );
      			}
     		}
      		if( list == "" )
      			write("当铺目前没有这种货品．\n");
      		else {
   			list = "你可以购买下列这些东西：\n"+list;
   			me->start_more(list);
      		}
   	}
   	else if( arg == "archery" )  {
     		list = "";
     		turn=0;
     		i=sizeof(goods);
     		while(i--) {
             		if(!goods[name[i]]) {
          			findbox()->delete_temp("numbers/"+name[i]);
          			findbox()->delete_temp("goods/"+name[i]);
          			continue;
             		}
      			if( goods[name[i]]->query("apply/skill_type") == arg )   {
      	   			++turn;
           			tlist = get_name(name[i]);
           			list += sprintf("%3d %-30s：%-20s：还剩%s%s\n",turn,tlist,
             			value_string(goods[name[i]]->query("value")),
             			chinese_number(findbox()->query_temp("numbers/"+name[i])),
             			goods[name[i]]->query("unit") );
      			}
     		}
      		if( list == "" )
      			write("当铺目前没有这种货品．\n");
      		else {
   			list = "你可以购买下列这些东西：\n"+list;
   			me->start_more(list);
      		}
   	}
   	else if( arg == "armor" || arg == "boots" || arg == "cloth" ||
    		arg == "finger" || arg == "hands" || arg == "head" || arg == "neck" ||
    		arg == "shield" || arg == "surcoat" || arg == "waist" ||
    		arg == "wrists" )   
	{
     		list = "";
     		turn=0;
     		i=sizeof(goods);
     		while(i--) {
             		if(!goods[name[i]]) {
          			findbox()->delete_temp("numbers/"+name[i]);
          			findbox()->delete_temp("goods/"+name[i]);
          			continue;
             		}
      			if( goods[name[i]]->query("armor_type") == arg )   {
      	   			++turn;
           			tlist = get_name(name[i]);
           			list += sprintf("%3d %-30s：%-20s：还剩%s%s\n",turn,tlist,
             					value_string(goods[name[i]]->query("value")),
             					chinese_number(findbox()->query_temp("numbers/"+name[i])),
             					goods[name[i]]->query("unit") );
      			}
     		}
      		if( list == "" )
      			write("当铺目前没有这种货品．\n");
      		else {
   			list = "你可以购买下列这些东西：\n"+list;
   			me->start_more(list);
      		}
   	}
   	else   
   	{
     		list = "";
     		turn=0;
     		i=sizeof(goods);
     		while(i--) {
             		if(!goods[name[i]]) {
          			findbox()->delete_temp("numbers/"+name[i]);
          			findbox()->delete_temp("goods/"+name[i]);
          			continue;
             		}
      			if( member_array(arg, goods[name[i]]->parse_command_id_list()) != -1 )   {
      	   			++turn;
           			tlist = get_name(name[i]);
           			list += sprintf("%3d %-30s：%-20s：还剩%s%s\n",turn,tlist,
             						value_string(goods[name[i]]->query("value")),
             						chinese_number(findbox()->query_temp("numbers/"+name[i])),
             						goods[name[i]]->query("unit") );
			 }
     		}
      		if( list == "" )
      			write("当铺目前没有这种货品．\n");
      		else {
   			list = "你可以购买下列这些东西：\n"+list;
   			me->start_more(list);
      		}
   	}
	return 1;
}

int do_buy(string arg)
{
	mapping goods;
   	string *name;
   	string fname;
   	object obj_file, ob;
   	int value, oldnum, afford, order;
   	int i, j;
   	object* inv;
   	string arg1, arg2;

   	if( this_player()->is_busy() )
     		return notify_fail("你现在正忙着呢。\n");
	if( !arg )  
		return err_msg("指令格式：buy <某物>\n");
   	if( sscanf(arg, "%s from %s", arg1, arg2) == 2 )   
     		arg = arg1;
	if( sscanf(arg, "%s %d", fname, order) != 2 )   
	{
     		fname = arg;
     		order = 1;
   	}
	if( !mapp(goods = findbox()->query_temp("goods")) )
     		return notify_fail("当铺目前没有任何货物可卖。\n");
   	name = keys(goods);
   	if(!sizeof(goods)) 
     		return notify_fail("当铺目前没有任何货物可卖。\n");
	j = 0;
   	i=sizeof(name);
   	while(i--) 
   	{
        	if(!goods[name[i]]) continue;
     		if( member_array(fname, goods[name[i]]->parse_command_id_list()) != -1 )  
			j++;    
     		if( j == order )   
     		{
       			obj_file = goods[name[i]];
          		value = obj_file->query("value"); 
          		if( !(afford=this_player()->can_afford(value)) )  
          			return err_msg("你没有足够的钱。\n");
                    	ob = new( base_name( obj_file ) ); 
       			ob->set_name(obj_file->query("name"),
         		obj_file->parse_command_id_list());
			if(!ob->move(this_player()))
         			return 0;
                     ob->set("value",0);
			this_player()->start_busy(1);
			arg = obj_file->query("name")+"("+obj_file->query("id")+")";
			oldnum = findbox()->query_temp("numbers/"+arg);
          		if(oldnum == 1)  
          		{
              			destruct(obj_file);
           			findbox()->delete_temp("numbers/"+arg);
           			findbox()->delete_temp("goods/"+arg);
          		}
          		else    findbox()->set_temp("numbers/"+arg, oldnum-1); 
			this_player()->pay_money(value);
     			message_vision("$N向当铺买下一" +ob->query("unit") + ob->query("name") + "。\n", this_player() );
			return 1;
     		}
   	}
	return err_msg("当铺里没有这种货品。\n");
}

int do_quit()
{
	object me=this_player();
        if( !valid_move(me) )
		return notify_fail("你被定住了，哪里退得出游戏！\n");
	if(!me->query_temp("suicide_countdown")) 
	{
		if( me->is_busy() )
			return notify_fail("( 你上一个动作还没有完成，不能退出。)\n");
	} //to allow halt suicide :D by mon 9/9/97
	message("system", me->name() + "离开游戏。\n", environment(me), me);
   	this_player()->move("/cmds/std/quitroom");
   	return 1;
}

// no clean up at hockshop to prevent items lose.
int clean_up()  
{
      return 0;
}

// strip away ansi color code.
// mon 5/7/98
string get_name(string str)
{
    string str1, str2;
    while(sscanf(str,"%s%*sm%s",str1,str2)==3)
	str=str1+str2;
    return str;
}
