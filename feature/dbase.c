// dbase.c
#include <ansi.h>
inherit F_TREEMAP;

mapping dbase;
nosave mapping tmp_dbase;
nosave mixed default_ob;

int LEVEL = 1;

int query_level(){ return LEVEL;}

int level_up()
{
	if( !objectp(this_object())
	 || !living(this_object()) 
	 || this_object()->is_ghost() )	 
		return 0;
	if( !this_object()->reward_gift() )
		return 0;
	this_object()->set("combat_exp",0);	
	LEVEL+= 1;
	return LEVEL;
}	

int level_lose()
{
	if( !objectp(this_object())
	 || !living(this_object()) 
	 || this_object()->is_ghost() )
		return 0;
	this_object()->gift_lose();
	LEVEL-= 1;
	if( LEVEL<1 )
		LEVEL = 1;
	return LEVEL;		
}

int set_level(int v)
{
	if( userp(this_object()) )
		return 0;
	LEVEL = v;
	return v;
}	

int init_level()
{
	LEVEL = 1;
	return LEVEL;
}


mixed query_default_object() { return default_ob; }
varargs mixed query_temp(string,int);
int delete_temp(string);
void set_default_object(mixed ob)
{
//	if( geteuid(previous_object()) != ROOT_UID )
//		error("dbase: Only this_object() or object with root euid can set default_ob.\n");
	if( !geteuid() ) seteuid(getuid());
	default_ob = ob;
           if(!ob) return;
	ob->add("no_clean_up", 1);
}

mixed set(string prop, mixed data)
{
	if( !mapp(dbase) ) dbase = ([]);

	if( strsrch(prop, '/')!=-1 )
		return _set( dbase, explode(prop, "/"), data );

	return dbase[prop] = data;
}

varargs mixed query(string prop, int raw)
{
	mixed data;

	if( !mapp(dbase) ) return 0;

	if( undefinedp(dbase[prop]) && (strsrch(prop, '/')!=-1) )
		data = _query(dbase, explode(prop, "/"));
	else
		data = dbase[prop];

	if( undefinedp(data) && default_ob )
		data = default_ob->query(prop, 1);

	if( raw ) return data;

	return evaluate( data, this_object() );
}

int delete(string prop)
{
	if( !mapp(dbase) ) return 0;

	if( strsrch(prop, '/')!=-1 )
		return _delete(dbase, explode(prop, "/"));
	else {
		map_delete(dbase, prop);
		return 1;
	}
}

mixed add(string prop, mixed data)
{
	mixed old;

	if( !mapp(dbase) || !(old = query(prop, 1)) )
		return set(prop, data);

	if( functionp(old) )
		error("dbase: add() - called on a function type property.\n");

	return set(prop, old + data);
}

mapping query_entire_dbase()
{
	return dbase;
}

mixed set_temp(string prop, mixed data)
{
	if( !mapp(tmp_dbase) ) tmp_dbase = ([]);

	if( strsrch(prop, '/')!=-1 )
		return _set( tmp_dbase, explode(prop, "/"), data );

	return tmp_dbase[prop] = data;
}

varargs mixed query_temp(string prop, int raw)
{
	mixed data;

	if( !mapp(tmp_dbase) ) return 0;

	if( strsrch(prop, '/')!=-1 )
		data = _query(tmp_dbase, explode(prop, "/"));
	else
		data = tmp_dbase[prop];

	if( functionp(data) && !raw )
		return (*data)( this_object() );
	else 
		return data;
}

int delete_temp(string prop)
{
	if( !mapp(tmp_dbase) ) return 0;

	if( strsrch(prop, '/')!=-1 )
		return _delete(tmp_dbase, explode(prop, "/"));
	else {
		map_delete(tmp_dbase, prop);
		return 1;
	}
}

mixed add_temp(string prop, mixed data)
{
	mixed old;

	if( !mapp(tmp_dbase) || !(old = query_temp(prop, 1)) )
		return set_temp(prop, data);

	if( functionp(old) )
		error("dbase: add_temp() - called on a function type property.\n");

	return set_temp(prop, old + data);
}

mapping query_entire_temp_dbase()
{
	return tmp_dbase;
}

//领悟
mapping knowing;

mapping query_knowing(){ return knowing;}

mixed is_knowing(string data)
{
	mapping kk;
	string mp;
	if( !knowing || !mapp(knowing) || !data || !stringp(data) )
		return 0;
	if( sscanf(data,"%s_%s",mp,data)!=2 )
		mp = "base";
	if( undefinedp(knowing[mp]) )
		return 0;
	kk = knowing[mp];
	if( undefinedp(kk[data]) )
		return 0;	
	return 	kk[data];
}

varargs int set_knowing(string data,mixed kn)
{
	mapping kk;
	string mp;
	if( !kn )
		kn = 1;	
	if( sscanf(data,"%s_%s",mp,data)!=2 )
		mp = "base";
	if( !mapp(knowing) ) 
	{
		kk = ([ data : kn ]);
        	knowing = ([ mp: kk ]);
        }
        else if( undefinedp(knowing[mp]) )
        {
		kk = ([ data : kn ]);
        	knowing = ([ mp: kk ]);
        }
        else
        {
        	kk = knowing[mp];
        	if( undefinedp(kk[data]) )
        	{
        		kk[data] = kn;
        		knowing[mp] = kk;
        	}
        	else
        	{
        		if( intp(kn) )
        			kk[data]+= kn;
        		else	kk[data] = kn;
        		knowing[mp] = kk;
        	}
        }	
	return 1;
}

int delete_knowing(string data)
{
	string mp;
	mapping kk;
	if( !is_knowing(data) )
		return 0;
	if( sscanf(data,"%s_%s",mp,data)!=2 )
		mp = "base";	
	kk = knowing[mp];	
	map_delete(kk,data);
	knowing[mp] = kk;
	return 1;
}

//新的金钱系统
mapping Gold; 
int default_gold = 0;
mapping Balance;

void init_money()
{
	if( default_gold>0 && !wizardp(this_object()) )
		return;
	Gold = ([
		"coin" 	: 0,
		"silver": 0,
		"gold"	: 0,
		"wan"	: 0,
		"yi"	: 0,
	]);	
	Balance = ([
		"coin" 	: 0,
		"silver": 0,
		"gold"	: 0,
		"wan"	: 0,
		"yi"	: 0,
	]);	
	default_gold = 1;
}

void init_balance()
{
}

string query_money()
{
	string str;
	if( !Gold || !mapp(Gold) )
		return "0";
	if( undefinedp(Gold["yi"])
	 && undefinedp(Gold["wan"])	
	 && undefinedp(Gold["gold"])
	 && undefinedp(Gold["silver"])
	 && undefinedp(Gold["coin"]) )
	 	return "0";
	if( Gold["yi"]==0 
	 && Gold["wan"]==0
	 && Gold["gold"]==0
	 && Gold["silver"]==0
	 && Gold["coin"]==0 )
	 	return "0";
	str = "";
	if( !undefinedp(Gold["yi"]) )		
		str+= Gold["yi"]!=0?chinese_number(Gold["yi"])+"亿":"";
	if( !undefinedp(Gold["wan"]) )
		str+= Gold["wan"]!=0?chinese_number(Gold["wan"])+"万":"";
	if( !undefinedp(Gold["gold"]) )
		str+= Gold["gold"]!=0?chinese_number(Gold["gold"])+"两":"";
	if( (!undefinedp(Gold["yi"]) && Gold["yi"]!=0)
	 || (!undefinedp(Gold["wan"]) && Gold["wan"]!=0)
	 || (!undefinedp(Gold["gold"]) && Gold["gold"]!=0) )
		str+= "黄金";	
	if( !undefinedp(Gold["silver"]) )		
		str+= Gold["silver"]!=0?chinese_number(Gold["silver"])+"两白银":"";
	if( !undefinedp(Gold["coin"]) )
		str+= Gold["coin"]!=0?chinese_number(Gold["coin"])+"文钱":"";
	return str;
}	

string query_balance()
{
	string str;
	if( !Balance || !mapp(Balance) )
		return "没有存款";
	if( undefinedp(Balance["yi"])
	 && undefinedp(Balance["wan"])	
	 && undefinedp(Balance["gold"])
	 && undefinedp(Balance["silver"])
	 && undefinedp(Balance["coin"]) )
	 	return "没有存款";	
	if( Balance["yi"]==0 
	 && Balance["wan"]==0
	 && Balance["gold"]==0
	 && Balance["silver"]==0
	 && Balance["coin"]==0 )
	 	return "没有存款";		
	str = "";
	if( !undefinedp(Balance["yi"]) )		
		str+= Balance["yi"]!=0?chinese_number(Balance["yi"])+"亿":"";
	if( !undefinedp(Balance["wan"]) )
		str+= Balance["wan"]!=0?chinese_number(Balance["wan"])+"万":"";
	if( !undefinedp(Balance["gold"]) )
		str+= Balance["gold"]!=0?chinese_number(Balance["gold"])+"两":"";
	if( (!undefinedp(Balance["yi"]) && Balance["yi"]!=0)
	 || (!undefinedp(Balance["wan"]) && Balance["wan"]!=0)
	 || (!undefinedp(Balance["gold"]) && Balance["gold"]!=0) )
		str+= "黄金";	
	if( !undefinedp(Balance["silver"]) )		
		str+= Balance["silver"]!=0?chinese_number(Balance["silver"])+"两白银":"";
	if( !undefinedp(Balance["coin"]) )
		str+= Balance["coin"]!=0?chinese_number(Balance["coin"])+"文钱":"";
	return str;
}

int init_check_money()
{
	int s,c,g,w,y,s2,c2,g2,w2,y2;
	if( !Gold || !mapp(Gold) )
		return 0;
	s2=c2=g2=w2=y2=0;	
	g = (int)Gold["gold"];
	w = (int)Gold["wan"];
	s = (int)Gold["silver"];
	c = (int)Gold["coin"];
	y = (int)Gold["yi"];
	if( y<0 )
		return 0;
	while( w<0 )
	{
		if( y>0 )
		{
			y = y-1;
			w+= 9999;
		}
		else	return 0;	
	}
	while(g<0 )
	{
		if( w>0 )
		{
			w = w-1;
			g+= 9999;
		}
		else	return 0;		
	}
	while(s<0)
	{
		if( g>0 )
		{
			g = g-1;
			s+= 99;
		}
		else	return 0;
	}
	while(c<0 )
	{
		if( s>0 )
		{
			s = s-1;
			c+= 99;
		}
		else	return 0;
	}
	Gold = ([
		"coin" 	: c,
		"silver": s,
		"gold"	: g,
		"wan"	: w,
		"yi"	: y,
	]);
	return 1;			
}	

int init_check_balance()
{
	int s,c,g,w,y,s2,c2,g2,w2,y2;
	if( !Balance || !mapp(Balance) )
		return 0;
	s2=c2=g2=w2=y2=0;	
	g = (int)Balance["gold"];
	w = (int)Balance["wan"];
	s = (int)Balance["silver"];
	c = (int)Balance["coin"];
	y = (int)Balance["yi"];
	if( y<0 )
		return 0;
	while( w<0 )
	{
		if( y>0 )
		{
			y = y-1;
			w+= 9999;
		}
		else	return 0;	
	}
	while(g<0 )
	{
		if( w>0 )
		{
			w = w-1;
			g+= 9999;
		}
		else	return 0;		
	}
	while(s<0)
	{
		if( g>0 )
		{
			g = g-1;
			s+= 99;
		}
		else	return 0;
	}
	while(c<0 )
	{
		if( s>0 )
		{
			s = s-1;
			c+= 99;
		}
		else	return 0;
	}
	Balance = ([
		"coin" 	: c,
		"silver": s,
		"gold"	: g,
		"wan"	: w,
		"yi"	: y,
	]);
	return 1;			
}	
//检查是否具有购买资格 v是给出的价格 0-否 1-是
int check_pay(int v)
{
	int s,c,g,w,y,s2,c2,g2,w2,y2;
	if( v<=0 || !Gold || !mapp(Gold) )
		return 0;
	if( !init_check_money() )
		return 0;		
	s2=c2=g2=w2=y2=0;	
	g = (int)Gold["gold"];
	w = (int)Gold["wan"];
	s = (int)Gold["silver"];
	c = (int)Gold["coin"];
	y = (int)Gold["yi"];
	
	c2 = v;
	if( c2/100 )
	{
		s2+= c2/100;
		c2 = c2%100;
	}
	if( s2/100 )
	{
		g2+= s2/100;
		s2 = s2%100;
	}
	if( g2/10000 )
	{
		w2+= g2/10000;
		g2 = g2%10000;
	}	
	if( w2/10000 )
	{
		y2+= w2/10000;
		w2 = w2%10000;
	}	
	if( y>y2 )	return 1;
	else if( y2>y ) return 0;
	else
	{
		if( w>w2 )	return 1;
		else if( w2>w )	return 0;
		else
		{
			if( g>g2 )	return 1;
			else if( g2>g )	return 0;
			else
			{
				if( s>s2 )	return 1;
				else if( s2>s )	return 0;
				else
				{
					if( c>c2 )	return 1;
					else if( c2>c ) return 0;
					else	return 1;
				}
			}
		}
			
	}
}				

//检查钱庄是否>=v 0-否 1-是
int check_balance(int v)
{
	int s,c,g,w,y,s2,c2,g2,w2,y2;
	if( v<=0 || !Balance || !mapp(Balance) )
		return 0;
	if( !init_check_balance() )
		return 0;
	s2=c2=g2=w2=y2=0;	
	g = (int)Balance["gold"];
	w = (int)Balance["wan"];
	s = (int)Balance["silver"];
	c = (int)Balance["coin"];
	y = (int)Balance["yi"];
	
	c2 = v;
	if( c2/100 )
	{
		s2+= c2/100;
		c2 = c2%100;
	}
	if( s2/100 )
	{
		g2+= s2/100;
		s2 = s2%100;
	}
	if( g2/10000 )
	{
		w2+= g2/10000;
		g2 = g2%10000;
	}	
	if( w2/10000 )
	{
		y2+= w2/10000;
		w2 = w2%10000;
	}	
	
	if( y>y2 )	return 1;
	else if( y2>y ) return 0;
	else
	{
		if( w>w2 )	return 1;
		else if( w2>w )	return 0;
		else
		{
			if( g>g2 )	return 1;
			else if( g2>g )	return 0;
			else
			{
				if( s>s2 )	return 1;
				else if( s2>s )	return 0;
				else
				{
					if( c>c2 )	return 1;
					else if( c2>c ) return 0;
					else	return 1;
				}
			}
		}
			
	}
}	
	
int money_add(int v)
{
	string str,log;
	int s,c,g,w,y,s2,c2,g2,w2,y2;
	if( v==0 )
		return 0;
	if( !Gold || !mapp(Gold) )
	{
		Gold = ([
			"gold"	: 0,
			"wan"	: 0,
			"silver": 0,
			"coin"	: 0,
			"yi"	: 0,
		]);	 
	}		
	g = (int)Gold["gold"];
	w = (int)Gold["wan"];
	s = (int)Gold["silver"];
	c = (int)Gold["coin"];
	y = (int)Gold["yi"];
	if( v>0 )
	{
		c+= v;
		if( c/100 )
		{
			s+= c/100;
			c = c%100;
		}
		if( s/100 )
		{
			g+= s/100;
			s = s%100;
		}
		if( g/10000 )
		{
			w+= g/10000;
			g = g%10000;
		}	
		if( w/10000 )
		{
			y+= w/10000;
			w = w%10000;
		}
	}
	else
	{
		v = -v;
		if( !check_pay(v) )
			return -1;
		else
		{
			if( c>=v )
				c = c-v;
			else
			{
				s2=c2=g2=w2=y2=0;	
				c2 = v;
				if( c2/100 )
				{
					s2+= c2/100;
					c2 = c2%100;
				}
				if( s2/100 )
				{
					g2+= s2/100;
					s2 = s2%100;
				}
				if( g2/10000 )
				{
					w2+= g2/10000;
					g2 = g2%10000;
				}	
				if( w2/10000 )
				{
					y2+= w2/10000;
					w2 = w2%10000;
				}

				if( y>0 )
				{
					y = y-1;
					w+= 10000;
				}
				if( w>0 )
				{
					w = w-1;
					g+= 10000;
				}
				if( g>0 )
				{
					g = g-1;
					s+= 100;
				}
				if( s>0 )
				{
					s = s-1;
					c+= 100;
				}
				
				y = y-y2;
				w = w-w2;
				g = g-g2;
				s = s-s2;
				c = c-c2;
		
				if( c/100 )
				{
					s+= c/100;
					c = c%100;
				}
				if( s/100 )
				{
					g+= s/100;
					s = s%100;
				}
				if( g/10000 )
				{
					w+= g/10000;
					g = g%10000;
				}	
				if( w/10000 )
				{
					y+= w/10000;
					w = w%10000;
				}	
			}
		}
	}
	Gold = ([
		"coin" 	: c,
		"silver": s,
		"gold"	: g,
		"wan"	: w,
		"yi"	: y,
	]);	
	
	return v;
}

int balance_add(int v)
{
	string str;
	int s,c,g,w,y,s2,c2,g2,w2,y2;
	if( v==0 )
		return 0;
	if( !Balance || !mapp(Balance) )
	{
		Balance = ([
			"gold"	: 0,
			"wan"	: 0,
			"silver": 0,
			"coin"	: 0,
			"yi"	: 0,
		]);	 
	}		
	g = (int)Balance["gold"];
	w = (int)Balance["wan"];
	s = (int)Balance["silver"];
	c = (int)Balance["coin"];
	y = (int)Balance["yi"];

	if( v>0 )
	{
		c+= v;
		if( c/100 )
		{
			s+= c/100;
			c = c%100;
		}
		if( s/100 )
		{
			g+= s/100;
			s = s%100;
		}
		if( g/10000 )
		{
			w+= g/10000;
			g = g%10000;
		}	
		if( w/10000 )
		{
			y+= w/10000;
			w = w%10000;
		}
	}
	else
	{
		v = -v;
		if( !check_balance(v) )
			return -1;
		else
		{
			if( c>=v )
				c = c-v;
			else
			{
				s2=c2=g2=w2=y2=0;	
				c2 = v;
				if( c2/100 )
				{
					s2+= c2/100;
					c2 = c2%100;
				}
				if( s2/100 )
				{
					g2+= s2/100;
					s2 = s2%100;
				}
				if( g2/10000 )
				{
					w2+= g2/10000;
					g2 = g2%10000;
				}	
				if( w2/10000 )
				{
					y2+= w2/10000;
					w2 = w2%10000;
				}

				if( y>0 )
				{
					y = y-1;
					w+= 10000;
				}
				if( w>0 )
				{
					w = w-1;
					g+= 10000;
				}
				if( g>0 )
				{
					g = g-1;
					s+= 100;
				}
				if( s>0 )
				{
					s = s-1;
					c+= 100;
				}
				
				y = y-y2;
				w = w-w2;
				g = g-g2;
				s = s-s2;
				c = c-c2;
		
				if( c/100 )
				{
					s+= c/100;
					c = c%100;
				}
				if( s/100 )
				{
					g+= s/100;
					s = s%100;
				}
				if( g/10000 )
				{
					w+= g/10000;
					g = g%10000;
				}	
				if( w/10000 )
				{
					y+= w/10000;
					w = w%10000;
				}	
			}
		}
	}			
	Balance = ([
		"coin" 	: c,
		"silver": s,
		"gold"	: g,
		"wan"	: w,
		"yi"	: y,
	]);	
	return v;
}

mixed _query_balance()
{
	return Balance;
}

mixed _query_money()
{
	return Gold;
}

//HP
mapping query_max_hp()
{
	int lvl,max_kee,max_sen,max_gin;
	lvl = this_object()->query_level();
	max_kee = lvl*50;
	max_sen = lvl*45;
	max_gin = lvl*3;
	if( !userp(this_object()) )
	{
		max_kee+= this_object()->query_temp("apply/max_kee");
		max_sen+= this_object()->query_temp("apply/max_sen");
	}	
	return ([
		"max_kee" : max_kee,
		"max_sen" : max_sen,
		"max_gin": max_gin,
	]);	
}

int query_max_exp()
{
	int p,lvl = this_object()->query_level();
	if( lvl>=140 )
		return 2000000000;
	p = ((lvl*lvl*lvl+60)/5*((lvl-1)*2+60))/100*1000;
	if( p<10000 )
		p = 10000;
	return p;	
}

int query_maxkee()
{
	int p,v = this_object()->query("max_kee");
	if( this_object()->query_skill("jingang-sanmei",2)>1 )
	{
		p = (this_object()->query_skill("jingang-sanmei",1)-100)/150+1;
		v = v*(100+p)/100;
	}
	v+= this_object()->query_temp("apply/max_kee");
	return v;
}

int query_maxgin()
{
	int v = this_object()->query_level();
	v = (v+1)*10;
	if( v<200 )
		v = 200;
	v+= this_object()->query_temp("apply/max_gin");
	if( this_object()->query_level()>=40 )
	{
		if( this_object()->query("shentong/40") )
			v+= 600;
		else	v+= 400;	
	}
        v+= (int)this_object()->query_int()*2;
	return v;
}

int query_maxsen()
{
	int p,v = this_object()->query("max_sen");
	if( this_object()->query_skill("jingang-sanmei",2)>1 )
	{
		p = (this_object()->query_skill("jingang-sanmei",1)-100)/150+1;
		v = v*(100+p)/100;
	}
	v+= this_object()->query_temp("apply/max_sen");
	return v;
}

int query_maxforce()
{
	int p,v = this_object()->query("max_force");
	if( this_object()->query_skill("jingang-zhenshen",2)>1 )
	{
		p = (this_object()->query_skill("jingang-zhenshen",1)-100)/150+1;
		v = v*(100+p)/100;
	}
	v+= this_object()->query_temp("apply/max_force");
	return v;
}

int query_maxmana()
{
	int p,v = this_object()->query("max_mana");
	if( this_object()->query_skill("tianlong-chanchang",2)>1 )
	{
		p = (this_object()->query_skill("tianlong-chanchang",1)-100)/150+1;
		v = v*(100+p)/100;
	}	
	v+= this_object()->query_temp("apply/max_mana");
	return v;
}
