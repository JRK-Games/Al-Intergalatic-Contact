class CleanerBotPawn extends UTPawn
	Placeable;

var Pawn P; // variable to hold the pawn we bump into
var() int DamageAmount; //how much brain to munch

simulated function PostBeginPlay()
{
	super.PostBeginPlay();

	//wake the physics up
	SetPhysics(PHYS_Falling);
}

//over-ride epics silly character stuff
simulated function SetCharacterClassFromInfo(class<UTFamilyInfo> Info)
{
	Return;
}

simulated event Bump(Actor Other, PrimitiveComponent OtherComp, Vector HitNormal)
{
	`Log("Bump");

	Super.Bump(Other, OtherComp, HitNormal);

	if ((Other == None) || Other.bStatic)
		return;

	P = Pawn(Other); //the pawn we might have bumped into

	if (P != None) //if we hit a pawn
	{
		if (CleanerBotPawn(Other) != None) //we hit another zombie
		{
			Return; //dont do owt
		}
		else
		{
			//use a timer so it just takes health once each encounter
			//theres other better ways of doing this probably
			SetTimer(0.1, false, 'EatSlow');
		}
	}
}

simulated function EatSlow()
{
	P.Health -= DamageAmount; // eat brains! mmmmm

	if (P.Health <= 0)//if the pawn has no health
	{
		P.Destroy(); //kill it
	}
}

defaultproperties
{
	Begin Object Name = WPawnSkeletalMeshComponent
	SkeletalMesh = SkeletalMesh'Game_AL.AI.CleanerBot'
	End Object

	RagdollLifespan = 180.0 //how long the dead body will hang around for

	AirSpeed = 50
	GroundSpeed = 50

	ControllerClass = class'AIMouse'
	bDontPossess = false

	DamageAmount = 10
}

My Controller Class :
class AIMouse extends GameAIController;

var Vector MyTarget;
var vector InFront;
var vector X, Y, Z;
var vector HitLoc, HitNormal;
var Actor	HitActor;

simulated event PostBeginPlay()
{
	super.PostBeginPlay();

	//start the brain going at 1 second intervals
	SetTimer(0.2, true, 'BrainTimer');
}

function BrainTimer()
{
	GetAxes(Pawn.Rotation, X, Y, Z);

	InFront = Pawn.Location + 50 * X;

	//trace in front
	HitActor = Trace(HitLoc, HitNormal, InFront, Pawn.Location);
	//DrawDebugSphere( HitLoc, 30, 10, 0, 255, 0 );


	//trace randomly left or right
	TraceRandom();

}
else //theres nothing in front
{
	//move forward
	MyTarget = InFront;
	GoToState('MoveAbout');
}

}

function TraceRandom()
{
	local int LeftRight;

	//make a random number
	LeftRight = Rand(50) - Rand(50);

	GetAxes(Pawn.Rotation, X, Y, Z);

	InFront = Pawn.Location + LeftRight * Y;

	//do another trace to a random location left or right
	HitActor = Trace(HitLoc, HitNormal, InFront, Pawn.Location);


	if (HitActor != None) //if we trace something
	{
		Return;
	}
	else //if we trace nothing
	{
		//move there
		MyTarget = InFront;
		GoToState('MoveAbout');
	}
}

state MoveAbout
{
Begin:

	MoveTo(MyTarget);
}

defaultproperties
{

}