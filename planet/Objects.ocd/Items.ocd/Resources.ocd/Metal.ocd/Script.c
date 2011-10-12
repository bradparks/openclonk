/*--- Metal ---*/

protected func Construction()
{
	if(GBackSemiSolid())
		SetGraphics("Old");
}

protected func Hit()
{
	Sound("MetalHit?");
	return 1;
}

public func IsFoundryProduct() { return true; }

local Name = "$Name$";
local Description = "$Description$";
local Collectible = 1;
local Rebuy = true;
