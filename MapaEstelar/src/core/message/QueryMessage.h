#pragma once

#include "BaseMessage.h"

enum QueryType {
	MSG_QUERY_REQUEST,
	MSG_QUERY_RESPONSE
};

enum QueryValue {
	MSG_QUERY_POSITION
};

struct QueryMessage : public BaseMessage {
	QueryType  type;
	QueryValue value;

	union {
		struct {
			float x;
			float y;
			float z;
			float w;
		} position;
	};
};