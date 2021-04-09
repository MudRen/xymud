// bank.c

inherit ROOM;

string money_str(int amount);
int pay_player(object who, int amount);

void init()
{
//      add_action("do_convert", "convert");
        add_action("do_deposit", "deposit");
        add_action("do_check", "account");
        add_action("do_withdraw", "withdraw");
        //add_action("do_quit", "quit");
}

int do_deposit(string arg)
{
        string what;
        int amount;
        object me;

        me = this_player();

        if(!arg || sscanf(arg, "%d %s", amount, what) !=2)
                return notify_fail("命令格式：deposit <数量> <货币单位>\n");
        if( this_player()->is_busy() )
                return notify_fail("你现在正忙着呢...。\n");
        if( amount<1 )
                return notify_fail("你要存多少？\n");
        switch(what)
        {
                case "coin"     : break;
                case "silver"   : amount*= 100;break;
                case "gold"     : amount*= 10000;break;
                default : return notify_fail("命令格式：deposit <数量> <货币单位>\n");
        }
        if( amount<1 )
                return notify_fail("你要存多少？\n");
        if( !me->check_pay(amount) )
                return notify_fail("你身上没有那么多钱。\n");   
        
        me->start_busy(1);
        message_vision(sprintf("$N拿出%s，存进了钱庄。\n",MONEY_D->money_str(amount,1)),me);
        me->money_add(-amount);
        me->balance_add(amount);
        me->save(1);
        return 1;
}

int do_check()
{
   string total = this_player()->query_balance();

   if(!total || total == "0")  
        return notify_fail("您在敝银庄没有存钱。\n");
   write("您在敝银庄共存有" +total+"。\n");
   return 1;
}

int do_withdraw(string arg)
{
        int amount, v, rv;
        string what;
        object me;

        me = this_player();

        if (!arg || sscanf(arg, "%d %s", amount, what) != 2)
                return notify_fail("命令格式：withdraw <数量> <货币单位>\n");
        if( this_player()->is_busy() )
                return notify_fail("你现在正忙着呢...。\n");
        if(time()-(int)me->query("withdraw_time")<60)
                return notify_fail("你取钱不能这么频繁。\n");
        if (amount < 1)
                return notify_fail("你想取出多少钱？\n");
        switch(what)
        {
                case "coin"     : break;
                case "silver"   : amount*= 100;break;
                case "gold"     : amount*= 10000;break;
                default : return notify_fail("命令格式：withdraw <数量> <货币单位>\n");
        }
        if( !me->check_balance(amount) )
                return notify_fail("你存的钱不够取。\n");
                
        me->start_busy(1);
        message_vision(sprintf("$N从钱庄取出了%s。\n",MONEY_D->money_str(amount,1)),me);
        me->balance_add(-amount);       
        me->money_add(amount);
        me->save(1);
        return 1;
}

