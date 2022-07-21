#pragma once

// << : 복사 생성자 방지
#define NO_COPY(className)	private :\
							className(const className& obj);\
							className* operator = (className* obj)\
							{return nullptr;}
// >> :


// << : 싱글톤 패턴
#define SINGLETONE(ClassName)	\
private:	\
NO_COPY(ClassName);\
ClassName(){}\
~ClassName(){}\
public:\
static ClassName* GetInst()\
{\
	if(m_pInst == NULL)\
		m_pInst = new ClassName;\
	return m_pInst;	\
}\
void DestroyInst()\
{\
	delete m_pInst;\
	m_pInst = nullptr;\
}\
private:\
static ClassName* m_pInst;
// >> :