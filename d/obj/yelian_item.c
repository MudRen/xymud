#include <dbase.h>
#include <name.h>
#include <ansi.h>
inherit F_CLEAN_UP;
inherit F_DBASE;
inherit F_MOVE;
inherit F_NAME;

nosave int amount;

void setup()
{
}

int query_amount() { return amount; }

private void destruct_me() { destruct(this_object()); }

void set_amount(int v)
{
object dest;
if( v < 0 )
        {
        amount=0; // mon 4/16/98
        call_out("destruct_me", 1);
        error("combine:set_amount less than 1.\n");
        }
if( v==0 ) 
        {
        amount = 0; // mon 4/16/98
        seteuid(getuid());
        dest=load_object("/cmds/std/quitroom");
        if(environment(this_object())!=dest)
                ::move(dest,1); // use the old move(), so
        call_out("destruct_me", 1);
        }
else    {
        amount = v;
        }
this_object()->set_weight(1000);
}

void add_amount(int v) { set_amount(amount+v); }

string short()
{
return ::short()+"("+query_amount()+query("base_unit")+")";
}

varargs int move(mixed dest, int silent)
{
object env, *inv;
int i, total, total0, result;
string file;

result= ::move(dest, silent);
reset_eval_cost();
if( env=environment()) 
        {
        file = base_name(this_object());
        inv = all_inventory(env);
        total = (int)query_amount();
        total0=total;
        for(i=0; i<sizeof(inv); i++) 
                {
                if ( inv[i]==this_object()
                  || inv[i]->name()!=this_object()->name() 
                  || inv[i]->query("item_level")!=this_object()->query("item_level") 
                  || inv[i]->name()!=this_object()->name() )
                        continue;
                if( base_name(inv[i])==file ) 
                        {
                        total += (int)inv[i]->query_amount();
                        destruct(inv[i]);
                        }
                }
        if( total!=total0 )
                set_amount(total);
        }
return result;
}

varargs string name(int v)
{
int lv; 
string arg,str = ::name(1);
lv = query("item_level");
switch(lv)
        {
        case 0:
        case 1: arg = NOR YEL"破碎"NOR"的";break;
        case 2: arg = NOR CYN"瑕疵"NOR"的";break;
        case 3: arg = NOR"";break;
        case 4: arg = NOR HIG"无暇"NOR"的";break;
        case 5: arg = NOR HIM"珍贵"NOR"的";break;
        default:arg = NOR HIC"完美"NOR"的";break;
        }
return arg+str;
}       

string query_yelian_type()
{
return this_object()->query("name");
}

int is_yelian()
{
return 1;
}

