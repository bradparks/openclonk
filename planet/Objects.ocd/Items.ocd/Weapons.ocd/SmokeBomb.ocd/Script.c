/**
	Smoke bomb
	Spreads lots of smoke.
		
	@author Maikel
*/


protected func Initialize()
{

	return;
}

public func ControlUse(object clonk, int x, int y)
{
	// If already active don't do anything and let the clonk throw it.
	if (GetEffect("IntSmokeBomb", this))
		return false;
	Fuse();
	return true;
}

public func Fuse()
{
	// Add smoking effect.
	if (!GetEffect("IntSmokeBomb", this))
		AddEffect("IntSmokeBomb", this, 100, 2, this);
	return;
}

protected func Hit()
{
	Sound("MetalHit?");
	return;
}


/*-- Smoking --*/

protected func FxIntSmokeBombStart(object target, proplist effect, int temp)
{
	if (temp)
		return FX_OK;
	// Interval and length.
	effect.Interval = 4;
	effect.length = 18 * 36;
	// Store particles.
	effect.lifetime = 24 * 36;
	effect.smoke =
	{
		R = 255,
		G = 255,
		B = 255,
		Alpha = PV_KeyFrames(1, 0, PV_Random(180, 210), 900, PV_Random(150, 180), 1000, 0),
		CollisionVertex = 1000,
		OnCollision = PC_Stop(),
		ForceX = PV_Wind(50, PV_Random(-2, 2)),
		ForceY = PV_Random(-2, 2),
		DampingX = PV_Linear(PV_Random(900, 1000), 500),
		DampingY = PV_Linear(PV_Random(900, 1000), 500),
		Rotation = PV_Random(0, 359),
		Size = PV_KeyFrames(0, 0, 4, 100, 12, 1000, 32),
		Phase = PV_Random(0, 15)
	};
	effect.smokethick = effect.smoke;
	effect.smokethick.Phase = PV_Random(0, 3);
	// Sound.
	Sound("Smoke.wav", false, 100, nil, +1);
	Sound("SmokeSizzle", false, 100, nil, +1);
	// Make non-collectible.
	this.Collectible = false;
	return FX_OK;
}

protected func FxIntSmokeBombTimer(object target, proplist effect, int time)
{
	if (time > effect.length)
		return FX_Execute_Kill;
		
	// Increas interval to draw more particles.
	if (time > effect.length / 6)
		effect.Interval = 4;
	if (time > effect.length / 4)
		effect.Interval = 3;
	if (time > effect.length / 3)
		effect.Interval = 2;
	if (time > 2 * effect.length / 3)
		effect.Interval = 1;

	// Particles for smoke and a bit of fire.		
	var smoke_dx = GetVertex(0, VTX_X);
	var smoke_dy = GetVertex(0, VTX_Y);
	var fuse_dx = GetVertex(1, VTX_X);
	var fuse_dy = GetVertex(1, VTX_Y);
	var smoke_life = effect.lifetime + Random(effect.lifetime) / 2;
	CreateParticle("Smoke", smoke_dx, smoke_dy, PV_Random(smoke_dx - 5, smoke_dx + 5),  PV_Random(smoke_dy - 5, smoke_dy + 5), smoke_life, effect.smoke);
	CreateParticle("SmokeThick", smoke_dx, smoke_dy,  PV_Random(smoke_dx - 5, smoke_dx + 5),  PV_Random(smoke_dy - 5, smoke_dy + 5), smoke_life, effect.smokethick);
	CreateParticle("Fire", fuse_dx, fuse_dy, PV_Random(2 * fuse_dx - 3, 2 * fuse_dx + 3),  PV_Random(2 * fuse_dy - 3, 2 * fuse_dy + 3), PV_Random(10, 20), Particles_Glimmer(), 2);
	
	return FX_OK;
}

protected func FxIntSmokeBombStop(object target, proplist effect, int reason, bool temp)
{
	if (temp)
		return FX_OK;
	// Sound.
	Sound("Smoke.wav", false, 100, nil, -1);
	Sound("SmokeSizzle", false, 100, nil, -1);
	RemoveObject();
	return FX_OK;
}

public func IsWeapon() { return true; }
public func IsArmoryProduct() { return true; }


/*-- Properties --*/

local Collectible = 1;
local Name = "$Name$";
local Description = "$Description$";
local UsageHelp = "$UsageHelp$";