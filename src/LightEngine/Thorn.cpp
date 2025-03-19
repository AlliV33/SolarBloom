#include "Thorn.h"
#include "TestScene.h"

Thorn::Thorn() : Enemy(THORN_HP) {}

void Thorn::OnInitialize()
{
    SetKineticBody(false);
    Enemy::OnInitialize();
    SetTagEnemy(TagEnemy::TThorn);
    SetRigidBody(true);
    mIsDead = false;
    mProximityRadius = GetSize().x * 1.5f + GetSize().x / 2 + player->GetSize().x / 2;
}

void Thorn::OnCollision(Entity* collidedWith)
{
    if (collidedWith->IsTag(TestScene::TAcid))
    {
        isActive1 = true;
    }

    if (collidedWith->IsTag(TestScene::TPlayer))
    {
        isActive = true;
    }
}

void Thorn::OnUpdate()
{
	if (isActive1)
	{
		mProgress1 += GetDeltaTime();
		if (canTakeDamage)
		{
			AddRemoveHP(-1);
			canTakeDamage = false;
		}
		else
		{
			if (mProgress1 >= mDelay1)
			{
				isActive1 = false;
				canTakeDamage = true;
				mProgress1 = 0.f;
			}
		}
	}

	if (isActive)
	{
		mProgress += GetDeltaTime();
		if (canDealDamage)
		{
            player->TransitionTo(Player::TakingDamage);
            canDealDamage = false;
		}
		else
		{
			if (mProgress >= mDelay)
			{
                isActive = false;
				canDealDamage = true;
				mProgress = 0.f;
			}
		}
	}

    if (mCooldownTimer > 0.0f)
    {
        mCooldownTimer -= GetDeltaTime();
    }

    else if (IsPlayerInProximity())
    {
        if (!mActionTriggered)
        {
            SetHitbox(GetSize().x * 3, GetSize().y);

            mActionTimer = 1.0f;
            mActionTriggered = true;
        }
    }

    if (mActionTriggered)
    {
        mActionTimer -= GetDeltaTime();
        if (mActionTimer <= 0.0f)
        {
            SetHitbox(GetSize().x, GetSize().y);

            mActionTriggered = false;
            mCooldownTimer = 3.0f;
        }
    }

    if (mIsDead)
    {
        Destroy();
    }
}

bool Thorn::IsPlayerInProximity()
{
    sf::Vector2f playerPosition = player->GetPosition();
    sf::Vector2f thornPosition = GetPosition();

    float distance = std::sqrt(std::pow(playerPosition.x - thornPosition.x, 2) + std::pow(playerPosition.y - thornPosition.y, 2));

    return distance <= mProximityRadius;
}