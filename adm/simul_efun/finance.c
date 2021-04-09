// Modified by Find.
#include <ansi.h>
nomask int check_money(object money,object me)
{
	if(!money || !me)
		return 0;

	if(!sscanf(file_name(money),"/obj/money/%*s"))
	{
		log_file("player/wiz_ob",sprintf("[%s] %s(%s)企图用伪钞(%s)购买商品被没收。\n",
		log_time(), me->name(1), geteuid(me), base_name(money) ));
		destruct(money);
		tell_object(me,"你身上的伪钞被系统没收了。\n");
		return 0;
	}

#ifdef WIZARD_FLAG
	if( money->query_wiz_flag() && !wizardp(me) )
	{
		log_file("player/wiz_ob",sprintf("[%s] %s(%s)企图用巫师给的钱%s购买商品被没收。\n",
		log_time(), me->name(1), geteuid(me), money_num(money->query_amount()) ));
		destruct(money);
		tell_object(me,"你身上存有巫师给你的钱被没收了。\n");
	}
#endif
	else
		return 1;
}

string money_num(int amount)
{
        string output;

        if (amount / 10000) {
                output = (amount / 10000) + "两黄金";
                amount %= 10000;
        }
        else
                output = "";
        if (amount / 100) {
                output = output + (amount / 100) + "两白银";
                amount %= 100;
        }
        if (amount)
                return output + (amount) + "文铜板";

        return output;
}

string money_e_num(int amount)
{
        string output;

        if (amount == 0)
        	return "0";
        if (amount / 10000) {
                output = (amount / 10000) + HIY"G"NOR;
                amount %= 10000;
        }
        else
                output = "";
        if (amount / 100) {
                output = output + (amount / 100) + WHT"S"NOR;
                amount %= 100;
        }
        if (amount)
                return output + (amount) + YEL"C"NOR;

        return output;
}
string money_c_num(int amount)
{
        string output;

        if (amount == 0)
        	return "0";
        if (amount / 10000) {
                output = (amount / 10000) + HIY"金"NOR;
                amount %= 10000;
        }
        else
                output = "";
        if (amount / 100) {
                output = output + (amount / 100) + WHT"银"NOR;
                amount %= 100;
        }
        if (amount)
                return output + (amount) + YEL"铜"NOR;

        return output;
}
string price_num(int amount)
{
	string output;
	
	if (amount < 1)
		amount = 1;
		
	if (amount / 10000) {
		output = amount / 10000 + "两黄金";
		amount %= 10000;
	} else output = "";
	
	if (amount / 100) {
		if (output != "")
			output += amount / 100 + "两白银";
		else
			output = amount / 100 + "两白银";

		amount %= 100;
	}
	
	if (amount)
		if (output != "")
			return output + amount + "文铜板";
		else
			return amount + "文铜板";
	
	return output;
}

nomask varargs void pay_player(object who, int amount)
{
	int v, flag = 0;
	object ob;
	string msg = "";

	seteuid(getuid());

	if (amount < 1)
		amount = 1;

	if (v = amount / 10000) {
		ob = new("/obj/money/gold");
		ob->set_amount(amount / 10000);

              if(!ob->move(who)) {
			flag = 1;
			who->add("balance",to_int(amount));
			msg += money_num(amount);
			destruct(ob);
		}
		else
		ob->move(who);                
		amount %= 10000;
	}
	
	if (amount / 100) {
		ob = new("/obj/money/silver");
		ob->set_amount(amount / 100);

              if(!ob->move(who)) {
			flag = 1;
			who->add("balance",to_int(amount));
			msg += money_num(amount);
			destruct(ob);
		}
		else
		ob->move(who);

		amount %= 100;
	}
	
	if (amount) {
		ob = new("/obj/money/coin");
		ob->set_amount(amount);

              if(!ob->move(who)) {
			flag = 1;
			who->add("balance",to_int(amount));
			msg += money_num(amount);
			destruct(ob);
		}
		else
		ob->move(who);
	}

	if(flag)
		tell_object(who,"您再也拿不下更多的东西，付您的钱"+msg+"已经存到您的钱庄账户上了。\n");

}

//玩家花费 从现金
nomask int player_pay(object who, int amount)
{
	object g_ob, s_ob, c_ob;
	int gc, sc, cc, left;
	int flag = 0;
	string msg = "";
	
	seteuid(getuid());
	
	if (g_ob = present("gold", who)) {
		if(!check_money(g_ob,who))
			gc = 0;
		else
		gc = g_ob->query_amount();
	} else
		gc = 0;

	if (s_ob = present("silver", who)) {
		if(!check_money(s_ob,who))
			sc = 0;
		else
		sc = s_ob->query_amount();
	} else
		sc = 0;

	if (c_ob = present("coin", who)) {
		if(!check_money(c_ob,who))
			cc = 0;
              else
		cc = c_ob->query_amount();
	} else
		cc = 0;
	
	if (cc + sc * 100 + gc * 10000 < amount) 
		if (present("thousand-cash", who))
			return 2;
		else 
			return 0;
	else {
		left = cc + sc * 100 + gc * 10000 - amount;
		gc = left / 10000;
		left = left % 10000;
		sc = left / 100;
		cc = left % 100;

		if (g_ob)
			g_ob->set_amount(gc);
		else sc += (gc * 100);

		if (s_ob)
		 	s_ob->set_amount(sc);
		else if (sc) {
			s_ob = new("/obj/money/silver");
			s_ob->set_amount(sc);

			if(!s_ob->move(who)) {
				flag = 1;
				destruct(s_ob);
				who->add("balance",sc);
				msg += money_num(sc);
			} else
			s_ob->move(who);
		}
		if (c_ob)
			c_ob->set_amount(cc);
		else if (cc) {
			c_ob = new("/obj/money/coin");
			c_ob->set_amount(cc);

			if(!c_ob->move(who)) {
				flag = 1;
				destruct(c_ob);
				who->add("balance",cc);
				msg += money_num(cc);
			} else
			c_ob->move(who);
		}

		if(flag)
			tell_object(who,"您再也拿不下更多的东西，找您的零钱"+msg+"已经存到您的钱庄账户上了。\n");

		return 1;
	}
}
//玩家花费 从银行卡
nomask int player_pay_card(object who, int amount)
{
	if ( !present("bank card",who) ) 
		return 2;
	else if ( (int)who->query("balance") < amount) 
		return 0;
	else
	who->add("balance",-amount);
		return 1;
}

nomask int can_afford(int amount)
{
        int total, cash_value;
        object cash, gold, silver, coin, me=this_player();

        cash = present("thousand-cash_money",me);
        gold = present("gold_money",me);
        silver = present("silver_money",me);
        coin = present("coin_money",me);

        total = 0;
        cash_value = 0;
        if( cash ) cash_value = cash->value();
        if( gold ) total += gold->value();
        if( silver ) total += silver->value();
        if( coin ) total += coin->value();

        if( (cash_value + total) < amount ) return 0;
        if( total < amount ) return 2;
        //if( total < amount ) return 0;

/*
        if( coin ) amount -= (int)coin->value();
        if( amount <= 0 ) return 1;
        else if( amount % 100 ) return 2;

        if( silver ) amount -= (int)silver->value();
        if( amount <= 0 ) return 1;
        else if( amount % 10000 ) return 2;
*/

        return 1;
}

nomask int pay_money(int amount)
{
        int total;
        object gold, silver, coin, me=this_player();
        int goldno, silverno, coinno;

        gold = present("gold_money",me);
        silver = present("silver_money",me);
        coin = present("coin_money",me);

        total = 0;
        if( gold ) total += gold->value();
        if( silver ) total += silver->value();
        if( coin ) total += coin->value();

        if( total < amount ) return 0;
        
        total -= amount;
        goldno = total/10000;
        silverno = (total % 10000) / 100;
        coinno = total % 100;

        if (!coin && coinno>0) 
           coin=new("/obj/money/coin");
        if (coin) coin->set_amount(coinno);
        if (coinno>0) coin->move(me);
        if ( coinno == 0 && coin) destruct(coin);

        if (!silver && silverno>0) 
           silver=new("/obj/money/silver");
        if (silver) silver->set_amount(silverno);
        if (silverno>0) silver->move(me);
        if (silverno == 0 && silver) destruct(silver);
   
        if (!gold && goldno>0) 
           gold=new("/obj/money/gold");
        if (gold) gold->set_amount(goldno);
        if (goldno>0) gold->move(me);
        if (goldno == 0 && gold) destruct(gold);

        me->save();
        return 1;
}

/*
// 取 env 所在地区的物件指数
nomask int price_ratio(object env)
{
	return FINANCE_D->price_domain(env);
}
*/