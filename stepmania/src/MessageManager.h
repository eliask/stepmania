/* MessageManager - Control lights. */

#ifndef MessageManager_H
#define MessageManager_H

#include <set>
#include <map>

class IMessageSubscriber
{
public:
	virtual void HandleMessage( const CString& sMessage ) = 0;
};

enum Message
{
	MESSAGE_CURRENT_SONG_CHANGED,
	NUM_MESSAGES
};
const CString& MessageToString( Message m );

template<class T, Message M>
class BroadcastOnChangePtr
{
private:
	T *val;
public:
	const T* Get() { return val; }
	void Set( T* t ) { val = t; MESSAGEMAN->Broadcast( MessageToString(M) ); }
	operator T* () const { return val; }
	T* operator->() const { return val; }
};

class MessageManager
{
public:
	MessageManager();
	~MessageManager();

	void Subscribe( IMessageSubscriber* pSubscriber, const CString& sMessage );
	void Subscribe( IMessageSubscriber* pSubscriber, Message m );
	void Unsubscribe( IMessageSubscriber* pSubscriber, const CString& sMessage );
	void Unsubscribe( IMessageSubscriber* pSubscriber, Message m );
	void Broadcast( const CString& sMessage );

private:
	typedef set<IMessageSubscriber*> SubscribersSet;
	map<CString,SubscribersSet> m_MessageToSubscribers;
};


extern MessageManager*	MESSAGEMAN;	// global and accessable from anywhere in our program

#endif

/*
 * (c) 2003-2004 Chris Danford
 * All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, and/or sell copies of the Software, and to permit persons to
 * whom the Software is furnished to do so, provided that the above
 * copyright notice(s) and this permission notice appear in all copies of
 * the Software and that both the above copyright notice(s) and this
 * permission notice appear in supporting documentation.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF
 * THIRD PARTY RIGHTS. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR HOLDERS
 * INCLUDED IN THIS NOTICE BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL INDIRECT
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */
