#include "CDatabaseResource.h"

CDatabaseResource::CDatabaseResource(int type,bool updateIndex)
{
	m_type=type;
	m_updateIndex=updateIndex;
	if ((type!=CREATE_ACTION)&&(type!=UPDATE_ACTION)&&(type!=DELETE_ACTION))
	{
		printf("Invalid resource type");
	}
	if (type!=UPDATE_ACTION)
	{
		m_updateIndex=true;
	}
}

int CDatabaseResource::merge(CResource *pResource)
{
	///����Դ���µ���Դ�ı�ʶ��ͬ����Դ����һ�������ݿ���Դ�����ҿ�����Ҫ�ϲ�
	CDatabaseResource *pDatabaseResource;
	pDatabaseResource=(CDatabaseResource *)pResource;
	switch (m_type)
	{
	case CREATE_ACTION:
		switch (pDatabaseResource->m_type)
		{
		case CREATE_ACTION:
			printf("impossible create action after create action");
			break;
		case UPDATE_ACTION:
			///ԭ����CREATE�����µĻ���CREATE������Ҫ�����κδ���
			///������޸ģ����ǲ���
			return RESOURCE_MERGE_OK;
		case DELETE_ACTION:
			///���ԭ����CREATE�����κ�����ֵ�������壬���Բ��ô���
			///�����ɾ��������ǿղ���
			m_type=NONE_ACTION;
			return RESOURCE_MERGE_OK;
		default:
			printf("Invalid resource action");
		}
		break;
	case UPDATE_ACTION:
		switch (pDatabaseResource->m_type)
		{
		case CREATE_ACTION:
			printf("impossible create action after update action");
			break;
		case UPDATE_ACTION:
			///ԭ����UPDATE����ԭ����ֵ�Ѿ��õ����棬����Ҳ�����������κδ�����ֻ��Ҫ����һ��updateIndex����
			m_updateIndex|=pDatabaseResource->m_updateIndex;
			///�޸ĺ��޸ģ������޸�
			return RESOURCE_MERGE_OK;
		case DELETE_ACTION:
			///���ԭ����UPDATE����ԭ����ֵ�Ѿ��õ����棬����Ҳ�����������κδ�����ֻ��Ҫ����һ��updateIndex����
			m_updateIndex=true;
			///�޸ĺ�ɾ������Ϊɾ������
			m_type=DELETE_ACTION;
			return RESOURCE_MERGE_OK;
		default:
			printf("Invalid resource action");
		}
		break;
	case DELETE_ACTION:
		switch (pDatabaseResource->m_type)
		{
		case CREATE_ACTION:
			//���Ѿ�ɾ����λ�����ִ�����һ���¶������������ģ�������Ҫ�ϲ�
			return RESOURCE_MERGE_FAIL_THIS;
		case UPDATE_ACTION:
			printf("impossible update after delete action");
			break;
		case DELETE_ACTION:
			printf("impossible delete after delete action");
			break;
		default:
			printf("Invalid resource action");
		}
		break;
	case NONE_ACTION:	//ע�⣬NONEֻ��һ������»���֣��Ǿ����ڴ�����ɾ��
		switch (pDatabaseResource->m_type)
		{
		case CREATE_ACTION:
			//���Ѿ�ɾ����λ�����ִ�����һ���¶������������ģ�������Ҫ�ϲ�
			return RESOURCE_MERGE_FAIL_THIS;
		case UPDATE_ACTION:
			printf("impossible update after delete action");
			break;
		case DELETE_ACTION:
			printf("impossible delete after delete action");
			break;
		default:
			printf("Invalid resource action");
		}
		break;
	}
	printf("Invalid datebase resource type");
	return RESOURCE_MERGE_FAIL_THIS;
}