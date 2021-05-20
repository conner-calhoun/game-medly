/**
 * Main game class
 */

import haxe.ds.Vector;
import h2d.Text;

typedef Node = {
	x:Int,
	y:Int
}

class Game extends hxd.App {
	public static var inst:Game;

	var hello:h2d.Text;
	var nodes:Array<Node>;

	var squarePieces:Array<Array<Node>>;

	// this works, but honestly needs to be done with a shader
	private function createSquare() {
		var x = 50;
		var y = 100;
		var d = 1;
		for (outer in 0...100) {
			squarePieces.insert(outer, []);
			for (inner in 0...100) {
				var node:Node = {x: x, y: y};
				squarePieces[outer].insert(inner, node);
				y += d;
			}
			y = 100;
			x += d;
		}
	}

	private function drawSquare() {
		var g = new h2d.Graphics(s2d);

		g.beginFill(0xFF0000);
		for (piece in squarePieces) {
			for (node in piece) {
				g.drawCircle(node.x, node.y, 2);
			};
		}
		g.endFill();
	}

	private function createLine() {
		var x = 50;
		var y = 50;
		var d = 2; // distance apart
		for (_ in 0...100) {
			var node:Node = {x: x, y: y};
			nodes.insert(0, node);

			x += d;
		}
	}

	private function drawLine() {
		var g = new h2d.Graphics(s2d);

		g.beginFill(0xFF0000);
		for (node in nodes) {
			g.drawCircle(node.x, node.y, 2);
		}
		g.endFill();
	}

	/**
	 * Called once at startup
	 */
	override function init() {
		// for loading sprites
		hxd.Res.initEmbed();

		hello = new h2d.Text(hxd.res.DefaultFont.get(), s2d);
		hello.text = "Heaps Jelly";
		hello.setPosition(5.0, 5.0);

		nodes = new Array<Node>();
		squarePieces = new Array<Array<Node>>();

		// draw a circle, not sure where to start on deforming it
		// possibly with a shader?
		createLine();
		createSquare();
	}

	/**
	 * Called once per frame
	 * @param dt time since last frame
	 */
	override function update(dt:Float) {
		drawLine();
		drawSquare();
	}

	/**
	 * Entry function
	 */
	public static function main() {
		inst = new Game();
	}
}
