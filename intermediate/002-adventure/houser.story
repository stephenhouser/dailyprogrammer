@ START
> You are in the kitchen and notice that an army of zombies is approaching your house.
> What will you do?
= KITCHEN

This and any other line that doesn't start with a command symbol is a comment.

@ KITCHEN
> You are in the kitchen. What will you do?
- M - GO INTO MUDROOM - MUDROOM
- B - LEAVE FROM THE BACK DOOR - DECK
- H - GO DOWN THE HALL - HALL
- L - GO INTO THE LIVING ROOM - LIVING_ROOM
- E - EAT SOME FOOD - KITCHEN_EAT

@ LIVING_ROOM
> You are in the living room. What will you do?
- K - GO INTO THE KITCHEN - KITCHEN
- 3 - 3D PRINT A KNIFE - MAKE_KNIFE
- F - GO OUT THE FRONT DOOR - FRONT_YARD

@ MAKE_KNIFE
> That was a good idea. You now have a knife! What will you do?
= LIVING_ROOM

@ KITCHEN_EAT
> Mmmmm. That was good. You are no longer hungry.
= KITCHEN

@ DECK
> You exited your house from the back door and are standing on the deck.
> What will you do?
- W - GO INTO THE BACK YARD - BACK_YARD
- K - GO INTO THE KITCHEN - KITCHEN

@ BACK_YARD
> With Zombies everywhere, you go into the woods and are never seen again.
= DIE

@ MUDROOM
> You are in the mudroom. What will you do?
- K - GO INTO THE KITCHEN - KITCHEN
- G - GO INTO THE GARAGE - GARAGE
- D - LEAVE FROM THE MUDROOM DOOR - FRONT_YARD
- E - EAT SOME FOOD - MUDROOM_EAT

@ MUDROOM_EAT
> Mmmmm. That was good. You are no longer hungry.
= MUDROOM

@ GARAGE
> The door is locked, you cannot get into the garage.
= MUDROOM

@ FRONT_YARD
> You exit your house into the front yard, the zombies are everywhere!
= DEFEND

@ HALL
> You are in the hall, it's dark but feels safe for the moment.
> What will you do?
- K - GO INTO THE KITCHEN - KITCHEN
- B - GO INTO BRIANNA'S ROOM - BRIANNA
- T - GO INTO THE TV ROOM - TV_ROOM
- A - GO INTO THE BATHROOM - BATHROOM

@ BRIANNA
> You are in Brianna's room. At first it feels safe, but there's a zombie 
> outside her window! What will you do?
- H - GO INTO THE HALL - HALL
- D - DEFEND YOURSELF - DEFEND

@ BATHROOM
> You are in the bathroom room. 
> outside her window! What will you do?
- H - GO INTO THE HALL - HALL
- 1 - GO PEE - PEE
- 2 - GO POOP - POOP

@ PEE
> You go pee and a zombie climbs up the toilet and kills you!
= DIE

@ POOP
> That felt good.
= BATHROOM

@ TV_ROOM
> You are in the TV Room.  What will you do?
- H - GO INTO THE HALL - HALL
- T - NETFLIX AND CHILL - NETFLIX

@ NETFLIX
> You try to watch Netflix but the only shows on are Zombie movies.
> What will you do?
- H - GO INTO THE HALL - HALL
- T - NETFLIX AND CHILL - NETFLIX
- K - KILL MYSELF - DIE

@ DEFEND
> How do you want to defend your home?
- K - USE A KNIFE - KNIFE
- S - USE A SHOTGUN - SHOTGUN

@ KNIFE
> The zombies are too many.
= DIE

@ SHOTGUN
> You take the shotgun.
= DIE

@ DIE
> You die.