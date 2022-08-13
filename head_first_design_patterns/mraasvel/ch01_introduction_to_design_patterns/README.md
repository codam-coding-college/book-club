# Introduction

	In this example we implement duck behaviors as a family of algorithms so that some ducks can have differing behaviors for flying and quacking.
	This is easily solved using the strategy design pattern.
	Using inheritance would provide the wrong behaviors to the wrong ducks whereas implementing it directly in the ducks would result in a lot of code duplication.

# Strategy Design Pattern

	Defines a family of algorithms. Encapsulates each one and lets them be used interchangeably.
	Strategy lets the algorithms vary independently from the clients that use it.
