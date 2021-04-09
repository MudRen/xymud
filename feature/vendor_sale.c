// vendor.c
#include <dbase.h>
inherit NPC_SAVE;

#define PERIOD 72000
// PERIOD is the renting length.
#define MINIMUM 100
// MINIMUM is the minimum amount of bid.

int price_ratio=10;
string owner_id, owner_name;
string owner_long;
string bidder, bidder_name;
string bidder_long;
int bid;
int deposit;
int close_time;
int profit;
int last_profit;

int take_money(int paid, int price);
void set_new_owner(string id, string name, string long);
void set_default_owner(); 
int query_price() {return price_ratio;}
int pay_back(string id, int amount);
void new_owner();

void set_time(int tim) {close_time=time()+tim;} //for debuging.

int buy_object(object me, string what)
{
	string ob;

	if( stringp(ob = query("vendor_goods/" + what)) )
	{
		if( ob->query("value")>10 )
			return ob->query("value")/10*price_ratio;
		else	return ob->query("value")*price_ratio/10;
	}
	else	return 0;
}

int complete_trade(object me, int num,string what)
{
	string ob_file,unit;
	object ob;
        int price,i;
	if( num<=0 )
		return 0;
	if( stringp(ob_file = query("vendor_goods/" + what)) ) 
	{
		int sale_price=price_ratio;

		for(i=0;i<num;i++)
		{
			ob = new(ob_file);
                 	if(!ob->move(me)&&i==0) 
                 	{
                 		if( ob ) destruct(ob);
                 		return 0;
                 	}
                	price=ob->query("value");
			if(sale_price>5)
		    		sale_price=5;
//                        ob->set_temp("sale_price", price*sale_price/10);
                        ob->set("value",0);
			if(!take_money(price*price_ratio/10, price)) 
			{
		    		destruct(ob);
		    		return 0;
			}
		}
		if( ob->query("base_unit") && ob->query_amount()>0 )
			unit = ob->query("base_unit");
		else if( ob->query("unit") )
			unit = ob->query("unit");	
		else	unit = "个";	
		message_vision("$N向"+this_object()->query("name")+"买下"+chinese_number(num) + unit + ob->query("name") + "。\n",me);
		return 1;
	}
	return notify_fail("没有这样东西卖。\n");
}

// price is the original price.
// paid is what the buyer paid.
int take_money(int paid, int price)
{
    	int earn;
	earn=paid-price/2;
	if(earn>=0)
		profit+=earn;
	else 
	{
		if(deposit+earn<0) 
		{
			message_vision("\n"+name()+"破产了！\n\n",this_object());
			new_owner();
			return notify_fail("the owner bankrupted\n");
		}
		deposit+=earn;
	}
	return 1;
}

string price_string(int v)
{
	return MONEY_D->money_str(v,1);
}

int do_vendor_list(string arg)
{
	mapping goods;
	string list, *name;
	int i;
	string tlist,n;

	if( !mapp(goods = query("vendor_goods")) ) return 0;
	if( arg && !this_object()->id(arg) ) return 0;
	name = keys(goods);
	list = "你可以购买下列这些东西：\n";
	for(i=0; i<sizeof(name); i++)  
	{
		n = goods[name[i]]->query("name");
		n = COLOR_D->clean_color(n); 
		tlist = sprintf("%s(%s)", n, name[i]);
		list += sprintf("%-30s：%s\n", tlist,price_string(goods[name[i]]->query("value")*price_ratio/10 ));
        }
	write(list);
	return 1;	
}

void init()
{
//	::init();
/*	
    	if(close_time<time()+60) new_owner();
    	if(!userp(this_player())) return;
*/    	
//        add_action("do_bid","bid");
//	add_action("do_deposit","deposit");
//    	add_action("do_setprice", "set_price");
//    	add_action("do_status","status");
	add_action("do_vendor_list", "list");
}

int do_bid(string arg)
{
    	int minimum, amount;
    	string money;
    	object who=this_player();
    	object who1;
    	string roomname;
    	object env;
    
    	notify_fail("Usage: bid <amount> <gold|silver>\n");

    	if(!arg) return 0;
    	if(sscanf(arg,"%d %s", amount, money)!=2) return 0;
    	if(money=="gold") amount*=10000;
    	else if(money=="silver") amount*=100;
    	else return 0;

    	if(amount<1) return 0;
    
    	if(!bid) minimum=MINIMUM;
    	else 
    	{
		minimum=bid;
		if(minimum>MINIMUM*10)
			minimum+=minimum/10;
		else	minimum+=MINIMUM;
    	}
    
    	minimum=(minimum/100)*100; // round to silver
    	if(amount<minimum) 
    		return notify_fail("你至少需要出"+price_string(minimum)+"。\n");
	if( !who->check_balance(amount) )
		return notify_fail("你户头里没有这么多钱。\n");
    	env=environment(this_object());
    	if(base_name(env)!=this_object()->query("startroom"))
		roomname=this_object()->query("name");
    	else	roomname=env->query("short");
	if(bidder) 
	{
		pay_back(bidder, bid);
		if(getuid(who)!=bidder) 
		{
	  		who1=find_player(bidder);
	  		if(who1)
	    			tell_object(who1, who->name()+"出价"+price_string(amount)+"收购"+roomname+"，你的投标失败了！\n");
		}
    	}

    	if(close_time<time()+120) close_time+=60; // postpone closing time // when there are new bidding.
    	
    	who->balance_add(-amount);
	bidder=who->query("id");
    	bidder_name=who->query("name");
    	bidder_long=who->long();
    	bid=amount;
	save();
    	message_vision("$N出价"+price_string(amount)+"收购"+roomname+"！\n",who);
    	return 1;
}
    
int pay_back(string id, int amount)
{
    	object who;
    
    	who=find_player(id);
    	if(who) 
    	{
		who->balance_add(amount);
		log_file("shop_log","pay "+amount+" to "+id+"\n");
		return 1;
    	} 
    	else 
    	{
		who=new(USER_OB);
		who->set("id",id);
		if(!who->restore()) 
		{
	    		log_file("shop_log","Failed to return "+amount+" coin to "+id+"\n");
	    		destruct(who);
	    		return 0;
		} 
		else 
		{
	    		who->add("balance",amount);
	    		log_file("shop_log","pay "+amount+" to "+id+"\n");
	    		destruct(who);
	    		return 1;
		}
    	}
}

int do_deposit(string arg)
{
    	object who=this_player();
    	string money;
    	int amount;
    
    	if(getuid(who)!=owner_id) 
    		return notify_fail("只有店主能用这个命令。\n");
    	notify_fail("Usage: deposit <amount> <gold|silver>\n");
	if(!arg) return 0;
    	if(sscanf(arg,"%d %s", amount, money)!=2) return 0;
    	if(money=="gold") amount*=10000;
    	else if(money=="silver") amount*=100;
    	else return 0;

    	if(amount<10000) return notify_fail("一次至少要一两金子。\n");
    	if(who->query("balance")<amount) 
    		return notify_fail("你户头里没有这么多钱。\n");
	who->balance_add(-amount);
	deposit+=amount;
    	save();
    	write("现在共有"+price_string(deposit)+"预付金。\n");
	return 1;
}

int do_setprice(string arg)
{
    	object who=this_player();
    	int ratio, max_price;
    	string str;
    
    	if(getuid(who)!=owner_id) 
    		return notify_fail("只有店主能用这个命令。\n");
	notify_fail("Usage: set_price <ratio> \n"+"<ratio> is between 1 to 100.\n");

    	if(!arg) return 0;
    	if(sscanf(arg,"%d",ratio)!=1) return 0;
    	if(ratio<1) return 0;
    	max_price=this_object()->query("max_price");
    	if(!max_price) max_price=100;
    	if(ratio>max_price) 
    		return notify_fail("定价必须少于"+chinese_number(max_price)+"。\n");
    	if(ratio<5 && deposit<1) 
    		return notify_fail("你的定价少于成本，必须先付定金(deposit)。\n");
    
    	price_ratio=ratio;
    	save();
    
    	if(ratio<10)
		message_vision("$N决定所有物品"+chinese_number(ratio)+"折出售。\n", who);
    	else if(ratio==10)
		message_vision("$N决定所有物品按原价出售。\n", who);
    	else 
    	{
		str=chinese_number(ratio/10);
		ratio=ratio-(ratio/10)*10;
		if(ratio) str+="点"+chinese_number(ratio);
		message_vision("$N决定所有物品按原价的"+str+"倍出售。\n", who);
    	}
    	return 1;
}

int do_status(string arg)
{
    	object who=this_player();
    	int hour, next;
    	string str;
    
    	if(!close_time) 
    	{
		close_time=time()+PERIOD;
		save();
    	}
    	next=close_time-time();
    	if(next<60)
		new_owner();
    	else 
    	{
		hour=next/3600;
		if(hour)
	  		str=chinese_number(hour)+"小时";
		else	str="";
		hour=(next-hour*3600)/60;
		if(hour)
	    		str+=chinese_number(hour)+"分种";
        	write("投标获胜者将于"+str+"后成为新店主。\n");
    	}
	if(bidder)
      		write("当前最高投标是"+bidder_name+"("+bidder+")："+price_string(bid)+"\n");
    	else	write("目前还没有人投标。\n");
	write("昨日盈利："+price_string(last_profit)+"\n");
	if(wizardp(who) || getuid(who)==owner_id) 
	{
		write("\n盈利　　　："+price_string(profit)+"\n");
		write("剩余预付金："+price_string(deposit)+"\n");
		write("价格指数　："+price_ratio+"\n");
		if(save())
	    		write("\n盈利存储完毕。\n"); // when owner check price, save data.
    	}
	return 1;
}

void new_owner()
{
    	int prof;
    	object old;
    	mapping mail;
    	object mbx;
    	string msg;

    	close_time=time()+PERIOD;
    
    	if(owner_id) 
    	{
		prof=profit+deposit;
		if(prof>0)
	    		pay_back(owner_id, prof);
		old=find_player(owner_id);

		msg="你的店主("+name(1)+")任期结束，结余"+price_string(prof)+"已存入你的户头。\n";
		msg+="其中盈利"+price_string(profit)+"，"+"剩余预付金"+price_string(deposit)+"。\n\n";
		if(old)
	    		tell_object(old,msg);

        	mail = ([
          		"from": name(1) + "(" + query("id") + ")",
          		"title": name(1)+"：帐目结算",
          		"to": owner_id,
          		"time": time(),
          		"status": "N",
          		"text": msg
        	]);
		seteuid(getuid());
		mbx=new(MAILBOX_OB);
		mbx->set_owner("vendor_sale");
		mbx->send_mail(owner_id,mail,1);
		destruct(mbx);
    	}
    	
    	if(bidder) 
    	{
		owner_id=bidder;
		owner_name=bidder_name;
		owner_long=bidder_long;
		set_new_owner(owner_id, owner_name, owner_long);
    	} 
    	else  
    	{
		owner_id=0;
		owner_name=0;
		owner_long=0;
		set_default_owner();
    	}
	last_profit=profit;
    	profit=0;
    	deposit=0;
    	bidder=0;
    	bidder_name=0;
    	bid=0;
    	price_ratio=10;
    	save();
}

// each NPC file can set two parameters: shop_id and shop_title
// shop_id: how to set player's id once they bought the shop.
// shop_title: how to set player's title.
void set_new_owner(string id, string name, string long)
{
	string short;
    	string *newid;

    	set_temp("apply/name",({name}));
    
    	if(pointerp(newid=query("shop_id"))) 
		newid=({newid[0]+" "+id})+newid;
    	else 	newid=({"boss "+id, "boss"}); // default setting
	
	set_temp("apply/id",newid);
    	set_temp("apply/long",({long}));

    	if(stringp(short=query("shop_title"))) 
		short+=" ";
    	else if(stringp(short=query("title"))) 
		short+=" ";
    	else	short=query("name")+" ";
    
    	short+=name+"("+capitalize(newid[0])+")";
    	set_temp("apply/short",({short}));
    	message_vision("\n新店主"+name+"走马上任！\n\n",this_object());
}

void set_default_owner()
{
	delete_temp("apply/name");
	delete_temp("apply/id");
	delete_temp("apply/short");
	delete_temp("apply/long");
}

void reload(string filename)
{
    	object me;
	::reload(filename);
    	if(owner_id)
		set_new_owner(owner_id, owner_name, owner_long);
	if(close_time<time()+120) close_time+=120; // postpone closing time when there are new bidding.
	
        me=this_object();
        me->set("eff_kee", (int)me->query("max_kee"));
        me->set("kee", (int)me->query("max_kee"));
        me->set("eff_sen", (int)me->query("max_sen"));
        me->set("sen", (int)me->query("max_sen"));
        me->set("force", (int)me->query("max_force"));
        me->set("atman", (int)me->query("max_atman"));
        me->set("mana", (int)me->query("max_mana"));
}

string query_save_file()
{
	string id;
    	id = query_save_name();
    	if( !stringp(id) ) 
    		return 0;
    	return sprintf(DATA_DIR "npc/boss/%s", id);
}

void die()
{ 
    	set("bellicosity",0);
	powerup(0,1);
	remove_all_killer();
	all_inventory(environment())->remove_killer(this_object());
	if(price_ratio>22)
		price_ratio=price_ratio*9/10; // decrease price after death.
    	save();
	return;
}

void remove()
{
       save(); // save profit data before this object is removed.
       ::remove();
}

void unconcious()
{
	die();
}