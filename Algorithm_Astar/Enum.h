#pragma once


enum class NODE_TYPE {
	START,
	END,
	NORMAL,
	OBSTACLE,
	OPEN,
	CLOSE,
	ROUTE,
	TYPEEND_NODE
};

enum class DIR_TYPE {
	PLUS,
	MUL,
	TYPEEND_DIR
};