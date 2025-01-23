#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
	//解放忘れ防止
	Finalize();
}

// インスタンスの削除
void GameObjectManager::DeleteInstance()
{
	// 自クラスのポインタ（実体をアドレスの先で保有）
	static GameObjectManager* instance = nullptr;

	// インスタンスが存在している場合、削除する
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

//初期化処理
void GameObjectManager::Initialize()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delta_second">１フレーム当たりの時間</param>
void GameObjectManager::Update(const float& delta_second)
{
	//生成できるオブジェクトをメイン配列に移動させる
	CheckCreateObject();

	// リスト内のオブジェクトを更新する
	for (GameObjectBase* obj : game_object)
	{
		obj->Update(delta_second);
	}

	// 当たり判定確認処理
	for (int i = 0; i < game_object.size(); i++)
	{
		// 移動の許可
		if (game_object[i]->GetMobility() == false)
		{
			continue;
		}

		// 見ているオブジェクトが同じであれば当たり判定を無くす
		for (int j = 0; j < game_object.size(); j++)
		{
			if (i == j)
			{
				continue;
			}

			//当たっているかをチェック
			CheckCollision(game_object[i], game_object[j]);
		}
	}

	//削除されるオブジェクトを配列に入れる
	CheckDesroyObject();
}

//描画処理
void GameObjectManager::Draw() const
{
	// オブジェクトリスト内のオブジェクトを描画する
	for (GameObjectBase* obj : game_object)
	{
		//メイン配列にいるオブジェクトの描画
		obj->Draw(screen_offset);
	}
}

//終了時処理
void GameObjectManager::Finalize()
{
	// オブジェクトリスト内のオブジェクトを破棄する
	DestoryAllObject();

	// 動的配列の解放
	if (!create_object.empty())
	{
		create_object.clear();
	}
	if (!destroy_object.empty())
	{
		destroy_object.clear();
	}
}

//生成するオブジェクトがあるかを見る
void GameObjectManager::CheckCreateObject()
{
	// 生成するオブジェクトがあれば、オブジェクトリスト内に挿入する
	if (!create_object.empty())
	{
		for (GameObjectBase* obj : create_object)
		{
			// レイヤー情報を基に順番を入れ替える
			int z_layer = obj->GetZLayer();
			std::vector<GameObjectBase*>::iterator itr = game_object.begin();	// オブジェクトリストの先頭
			// リストの末尾になるまで走査する
			for (; itr != game_object.end(); itr++)
			{
				// Zレイヤーが大きい場所に要素を追加する
				// 例 itr->ZLayer{1, 1, 2, 3}、z_layer = 2 の時
				//    itr->ZLayer{1, 1, 2, z_layer, 3}とする
				if (z_layer < (*itr)->GetZLayer())
				{
					break;
				}
			}
			// リストの途中に挿入する
			game_object.insert(itr, obj);
		}
		// 生成リストを解放する
		create_object.clear();
	}
}

//削除されるオブジェクトがあるかを見る
void GameObjectManager::CheckDesroyObject()
{
	// 破棄リスト内が空でない場合、リスト内のオブジェクトを破棄する
	if (!destroy_object.empty())
	{
		for (GameObjectBase* obj : destroy_object)
		{
			std::vector<GameObjectBase*>::iterator itr = game_object.begin();	// オブジェクトリストの先頭
			// リストの末尾になるまで走査する
			for (; itr != game_object.end(); itr++)
			{
				// リスト内にあれば、削除する
				if ((*itr) == obj)
				{
					game_object.erase(itr);
					obj->Finalize();
					delete obj;
					break;
				}
			}
		}
	}
}

//std::vector<GameObjectBase*>& GameObjectManager::CreateGameObject()
//{
//	return ;
//}

//削除配列にいるオブジェクトを削除する
void GameObjectManager::DestroyGameObject(GameObjectBase* target)
{
	// ヌルポチェック
	if (target == nullptr)
	{
		return;
	}

	// 破棄オブジェクトリスト内にあれば、追加しない
	for (GameObjectBase* obj : destroy_object)
	{
		if (obj == target)
		{
			return;
		}
	}

	// 破棄を行うオブジェクトリストに追加する
	destroy_object.push_back(target);
}

/// <summary>
/// 当たり判定のチェック
/// </summary>
/// <param name="target">例：プレイヤー</param>
/// <param name="partner">例：敵</param>
void GameObjectManager::CheckCollision(GameObjectBase* target, GameObjectBase* partner)
{
	// 中身が入っているかをチェック
	if (target == nullptr || partner == nullptr)
	{
		return;
	}

	// 当たり判定情報を取得
	BoxCollision tc = target->GetCollision();
	BoxCollision pc = partner->GetCollision();

	// 当たり判定が有効か確認する
	if (tc.IsCheckHitTarget(pc.object_type) || pc.IsCheckHitTarget(tc.object_type))
	{
		// 対角線上の頂点座標を求める
		// target矩形の左上の座標を求める
		tc.point[0] += target->GetLocation() - target->GetBoxSize();
		// targt矩形の右下の座標を求める
		tc.point[1] += target->GetLocation() + target->GetBoxSize();
		// partner矩形の左上の座標を求める
		pc.point[0] += partner->GetLocation() - partner->GetBoxSize();
		// partner矩形の右下の座標を求める
		pc.point[1] += partner->GetLocation() + partner->GetBoxSize();

		// カプセル同士の当たり判定
		if (IsCheckCollision(tc, pc))
		{
			// 当たっていることを通知する
			target->OnHitCollision(partner);
			partner->OnHitCollision(target);
		}

	}
}

const Vector2D GameObjectManager::GetScreenOffset() const
{
	return screen_offset;
}

//メイン配列にいるオブジェクトを全て削除
void GameObjectManager::DestoryAllObject()
{
	// オブジェクトリストが空なら処理を終了する
	if (game_object.empty())
	{
		return;
	}
	// オブジェクトリスト内のオブジェクトを削除する
	for (GameObjectBase* obj : game_object)
	{
		obj->Finalize();
		delete obj;
	}
	// 動的配列の解放
	game_object.clear();
}