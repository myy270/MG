//=============================================================================
//
// ���^�n�ʂ̏��� [field_star.cpp]
// Author : HAL�����@GP11C295�@����@�E��
//
//=============================================================================
#include "player.h"
#include "input.h"
#include "enemy.h"
#include "bullet.h"
#include "Hitjudge.h"
#include "field_star.h"


//*************�L�����N�^�[�f�[�^�ϐ��̗p��*****************************
PLAYER	FieldStar[NUM_SKY];			//�v���C���[�L�����N�^�\����

//*********************���f���f�[�^�t�@�C�����z��********************
const char* FieldStarModelData[] = 
{
	"data/MODEL/sample_field.x",
};


//=============================================================================
// ����������
//=============================================================================
HRESULT InitFieldStar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3	temp;
	D3DXMATRIX mtxScl,/*mtxRot,*/ mtxTranslate;

	// �L�����N�^�̈ʒu�E��]�E�X�P�[���Ȃǂ̏����ݒ�
	for (int i = 0; i < NUM_SKY; i++)
	{

			FieldStar[i].part[0].srt.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//
			FieldStar[i].part[0].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//

			FieldStar[i].part[0].use = TRUE;
			FieldStar[i].part[0].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&FieldStar[i].part[0].mtxWorld);

			// �X�P�[�����s��ɂ��ă��[���h�s��i�n�߂͒P�ʍs��j�Ə�Z
			temp = FieldStar[i].part[0].srt.scl;
			D3DXMatrixScaling(&mtxScl, temp.x, temp.y, temp.z);
			D3DXMatrixMultiply(&FieldStar[i].part[0].mtxWorld, &FieldStar[i].part[0].mtxWorld, &mtxScl);

			// ��]���s��ɂ��ă��[���h�s��Ə�Z
			temp = FieldStar[i].part[0].srt.rot;
			D3DXMatrixRotationYawPitchRoll(&FieldStar[i].part[0].mtxRot, temp.y, temp.x, temp.z);
			D3DXMatrixMultiply(&FieldStar[i].part[0].mtxWorld, &FieldStar[i].part[0].mtxWorld, &FieldStar[i].part[0].mtxRot);

			// �ړ����s��ɂ��ă��[���h�s��Ə�Z
			temp =FieldStar[i].part[0].srt.pos;
			D3DXMatrixTranslation(&mtxTranslate, temp.x, temp.y, temp.z);
			D3DXMatrixMultiply(&FieldStar[i].part[0].mtxWorld, &FieldStar[i].part[0].mtxWorld, &mtxTranslate);

			// �����������[���h�}�g���b�N�X��DirectX�փZ�b�g
			pDevice->SetTransform(D3DTS_WORLD, &FieldStar[i].part[0].mtxWorld);


		//���f���f�[�^�̏����ݒ�
		for (int i = 0; i < NUM_SKYMODEL; i++)
		{
			FieldStar[i].part[0].pD3DTextureModel = NULL;
			FieldStar[i].part[0].pMesh = NULL;
			FieldStar[i].part[0].pMatBuff = NULL;
			FieldStar[i].part[0].nNumMat = 0;


			if (D3D_OK != D3DXLoadMeshFromX(FieldStarModelData[0],			// �ǂݍ��ރ��f���t�@�C����(X�t�@�C��)
												D3DXMESH_SYSTEMMEM,		// ���b�V���̍쐬�I�v�V�������w��
												pDevice,				// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
												NULL,					// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
												&FieldStar[0].part[0].pMatBuff,	// �}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^
												NULL,				// �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
												&FieldStar[0].part[0].nNumMat,		// D3DXMATERIAL�\���̂̐�
												&FieldStar[0].part[0].pMesh))	// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
			{
				return E_FAIL;
			}
			
		}
	}


	// �e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
	//	TEXTURE_SKY,						// �t�@�C���̖��O
	//	&FieldStar[0].part[0].pD3DTextureModel);	// �ǂݍ��ރ������[
		
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitFieldStar(void)
{


	for(int i=0; i< NUM_SKYMODEL; i++)
	{
		if( NULL !=FieldStar[i].part[0].pD3DTextureModel)
		{
			FieldStar[i].part[0].pD3DTextureModel->Release();
			FieldStar[i].part[0].pD3DTextureModel = NULL;
		}

		if( NULL !=FieldStar[i].part[0].pMesh)
		{
			FieldStar[i].part[0].pMesh->Release();
			FieldStar[i].part[0].pMesh = NULL;
		}

		if( NULL !=FieldStar[i].part[0].pMatBuff)
		{
			FieldStar[i].part[0].pMatBuff->Release();
			FieldStar[i].part[0].pMatBuff = NULL;
		}
	}


}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateFieldStar(void)
{

}


//=============================================================================
// �`�揈��
//=============================================================================
void DrawFieldStarModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl,/*mtxRot,*/ mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;



	// ���ݐݒ肳��Ă���}�e���A�����擾���ĕۑ�
	pDevice->GetMaterial(&matDef);


	//*************************�S�ẴL�����N�^�[��\��************************
	for(int i=0; i<NUM_SKY; i++)
	{
		D3DXVECTOR3	temp;

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&FieldStar[i].part[0].mtxWorld);

		// �X�P�[�����s��ɂ��ă��[���h�s��i�n�߂͒P�ʍs��j�Ə�Z
		temp = FieldStar[i].part[0].srt.scl;
		D3DXMatrixScaling(&mtxScl, temp.x, temp.y, temp.z);
		D3DXMatrixMultiply(&FieldStar[i].part[0].mtxWorld, &FieldStar[i].part[0].mtxWorld, &mtxScl);

		// ��]���s��ɂ��ă��[���h�s��Ə�Z
		temp = FieldStar[i].part[0].srt.rot;
		D3DXMatrixRotationYawPitchRoll(&FieldStar[i].part[0].mtxRot, temp.y, temp.x, temp.z);
		D3DXMatrixMultiply(&FieldStar[i].part[0].mtxWorld, &FieldStar[i].part[0].mtxWorld, &FieldStar[i].part[0].mtxRot);

		// �ړ����s��ɂ��ă��[���h�s��Ə�Z
		temp =FieldStar[i].part[0].srt.pos;
		D3DXMatrixTranslation(&mtxTranslate, temp.x, temp.y, temp.z);
		D3DXMatrixMultiply(&FieldStar[i].part[0].mtxWorld, &FieldStar[i].part[0].mtxWorld, &mtxTranslate);

		// �����������[���h�}�g���b�N�X��DirectX�փZ�b�g
		pDevice->SetTransform(D3DTS_WORLD, &FieldStar[i].part[0].mtxWorld);

		// ���f���̃}�e���A�����ɑ΂���|�C���^���擾
		pD3DXMat = (D3DXMATERIAL*)FieldStar[i].part[0].pMatBuff->GetBufferPointer();

		//���f���̏��ɏ]���ă��f�����\������I�u�W�F�N�g�̐������J��Ԃ�
		for (int nCntMat = 0; nCntMat < (int)FieldStar[i].part[0].nNumMat; nCntMat++)
		{
			// �I�u�W�F�N�g�̃}�e���A���̐ݒ�
			pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

			// �I�u�W�F�N�g�̃e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, FieldStar[i].part[0].pD3DTextureModel);

			// �I�u�W�F�N�g�̕`��
			FieldStar[i].part[0].pMesh->DrawSubset(nCntMat);
		}
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);

}

