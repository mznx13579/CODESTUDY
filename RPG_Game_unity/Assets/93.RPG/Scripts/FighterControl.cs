using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FighterControl : MonoBehaviour
{
    [Header("이동관련속성")]
    [Tooltip("기본이동속도")]
    public float MoveSpeed = 3.0f;
    public float RunSpeed = 5.0f;
    public float DirectionRotateSpeed = 100.0f;
    public float BodyRotateSpeed = 6.0f;
    [Range(0.01f, 5.0f)]
    public float VelocityChangeSpeed = 0.1f;
    private Vector3 CurrentVelocity = Vector3.zero;
    private Vector3 MoveDirection = Vector3.zero;
    private CharacterController myCharacterController = null;
    private CollisionFlags collisionFlags = CollisionFlags.None;
    private float gravity = 9.8f;
    private float verticalSpeed = 0.0f;
    private bool CannotMove = false;

    
    [Header("애니메이션관련속성")]
    public AnimationClip IdleAnimClip = null;
    public AnimationClip WalkAnimClip = null;
    public AnimationClip RunAnimClip = null;
    public AnimationClip Attack1AnimClip = null;
    public AnimationClip Attack2AnimClip = null;
    public AnimationClip Attack3AnimClip = null;
    public AnimationClip Attack4AnimClip = null;
    public AnimationClip SkillAnimClip = null;
    private Animation myAnimation = null;

    public enum FighterState { None, Idle, Walk, Run, Attack, Skill}
    [Header("캐릭터상태")]
    public FighterState myState = FighterState.None;

    public enum FighterAttackState { Attack1, Attack2, Attack3, Attack4 }
    public FighterAttackState AttackState = FighterAttackState.Attack1;
    public bool NextAttack = false; // 다음 공격 활성화 여부 확인 플래그
    
    [Header("전투 관련")]
    public TrailRenderer AttackTrailRenderer = null;
    public CapsuleCollider AttackCapsuleCollider = null;
    public GameObject SkillEffect = null;


    // Start is called before the first frame update
    void Start()
    {
        myCharacterController = GetComponent<CharacterController>();

        myAnimation = GetComponent<Animation>();
        myAnimation.playAutomatically = false;
        myAnimation.Stop();

        myState = FighterState.Idle;
        myAnimation[IdleAnimClip.name].wrapMode = WrapMode.Loop;
        myAnimation[WalkAnimClip.name].wrapMode = WrapMode.Loop;
        myAnimation[RunAnimClip.name].wrapMode = WrapMode.Loop;
        myAnimation[Attack1AnimClip.name].wrapMode = WrapMode.Once;
        myAnimation[Attack2AnimClip.name].wrapMode = WrapMode.Once;
        myAnimation[Attack3AnimClip.name].wrapMode = WrapMode.Once;
        myAnimation[Attack4AnimClip.name].wrapMode = WrapMode.Once;
        myAnimation[SkillAnimClip.name].wrapMode = WrapMode.Once;

        AddAnimationEvent(Attack1AnimClip, "OnAttackAnimFinished");
        AddAnimationEvent(Attack2AnimClip, "OnAttackAnimFinished");
        AddAnimationEvent(Attack3AnimClip, "OnAttackAnimFinished");
        AddAnimationEvent(Attack4AnimClip, "OnAttackAnimFinished");
        AddAnimationEvent(SkillAnimClip, "OnSkillAnimFinished");
               
    }

    // Update is called once per frame
    void Update()
    {
        Move();
        BodyDirectionChange();
        AnimationControl();
        CheckState();
        InputControl();
        ApplyGravity();
        AttackComponentControl();
    }
    /// <summary>>
    /// 이동 관련 함수
    /// <summary>
    void Move()
    {
        if(CannotMove == true)
        {
            return;
        }
        Transform CameraTransform = Camera.main.transform;
        Vector3 forward = CameraTransform.TransformDirection(Vector3.forward);//실제 카메라가 바라보는 방향이 월드 상에서는 어떤 방향인지
        forward.y = 0.0f;
        Vector3 right = new Vector3(forward.z, 0.0f, -forward.x);
        
        float vertical = Input.GetAxis("Vertical");//w,s
        float horizontal = Input.GetAxis("Horizontal");//a,d

        Vector3 targetDirection = horizontal * right + vertical * forward; //이동하고자 하는 방향
        MoveDirection = Vector3.RotateTowards(MoveDirection, targetDirection, DirectionRotateSpeed * Mathf.Deg2Rad * Time.deltaTime, 1000.0f);
        MoveDirection = MoveDirection.normalized;

        float speed = MoveSpeed;
        if(myState == FighterState.Run)
        {
            speed = RunSpeed;
        }
        Vector3 gravityVector = new Vector3(0.0f, verticalSpeed, 0.0f);
        Vector3 moveAmount = (MoveDirection * speed * Time.deltaTime) + gravityVector;
        collisionFlags = myCharacterController.Move(moveAmount);
        
    }   
    private void OnGUI()
    {
        GUILayout.Label("충돌 :" + collisionFlags.ToString());
        GUILayout.Label("현재 속도 : " + GetVelocitySpeed().ToString());
        if(myCharacterController != null && myCharacterController.velocity != Vector3.zero)
        {
            GUILayout.Label("current Velocity Vector : " + myCharacterController.velocity.ToString());
            GUILayout.Label("current Velocity Magnitude : " + myCharacterController.velocity.magnitude.ToString());
        }
    }
    /// <summary>
    /// 현재 내 캐릭터의 이동속도 얻어옴
    /// <summary>
    float GetVelocitySpeed()
    {
        if(myCharacterController.velocity == Vector3.zero)
        {
            CurrentVelocity = Vector3.zero;
        } 
        else
        {
            Vector3 goalVelocity = myCharacterController.velocity;
            goalVelocity.y = 0.0f;
            CurrentVelocity = Vector3.Lerp(CurrentVelocity, goalVelocity, VelocityChangeSpeed * Time.fixedDeltaTime);
        }
        return CurrentVelocity.magnitude;
    }
    /// <summary>
    /// 몸통의 방향을 이동방향으로 변경
    /// <summary>
    
    void BodyDirectionChange()
    {
        if(GetVelocitySpeed() > 0.0f)//움직인다면
        {
            Vector3 newForward = myCharacterController.velocity;
            newForward.y = 0.0f;
            transform.forward = Vector3.Lerp(transform.forward, newForward, BodyRotateSpeed * Time.deltaTime);
        }
    }
    /// <summary>
    /// 애니메이션을 재생시키는 함수
    /// <summary>
    void AnimationPlay(AnimationClip clip)
    {
        myAnimation.clip = clip;
        myAnimation.CrossFade(clip.name);
    }
    void AnimationControl()
    {
        switch(myState)
        {
            case FighterState.Idle:
                AnimationPlay(IdleAnimClip);
                break;
            case FighterState.Walk:
                AnimationPlay(WalkAnimClip);
                break;
            case FighterState.Run:
                AnimationPlay(RunAnimClip);
                break;
            case FighterState.Attack:
                AttackAnimationControl(); // 공격상태에 맞춘 애니메이션 재생
                break;
            case FighterState.Skill:
                AnimationPlay(SkillAnimClip);
                break;
        }
    }
    /// <summary>
    /// 상태 변경 함수
    /// <summary>
    void CheckState()
    {
        float currentSpeed = GetVelocitySpeed();
        switch(myState)
        {
            case FighterState.Idle:
                if(currentSpeed > 0.0f)
                {
                    myState = FighterState.Walk;
                }
                break;
            case FighterState.Walk:
                if(currentSpeed > 0.5f)
                {
                    myState = FighterState.Run;
                } else if(currentSpeed < 0.01f)
                {
                    myState = FighterState.Idle;
                }
                break;
            case FighterState.Run:
                if(currentSpeed < 0.5f)
                {
                    myState = FighterState.Walk;
                }
                if(currentSpeed < 0.01f)
                {
                    myState = FighterState.Idle;
                }
                break;
            case FighterState.Attack:
                CannotMove = true;
                break;
            case FighterState.Skill:
                CannotMove = true;
                break;
        }
    }
    
    void InputControl()
    {
        if(Input.GetMouseButtonDown(0) == true) // 0 : Mouse Left Button
        {
            if(myState != FighterState.Attack)
            {
                myState = FighterState.Attack;
                AttackState = FighterAttackState.Attack1;
            } else { // Being Attack
                switch(AttackState)
                {
                    case FighterAttackState.Attack1:
                        if(myAnimation[Attack1AnimClip.name].normalizedTime > 0.1f)
                        {
                            NextAttack = true;
                        }
                        break;
                    case FighterAttackState.Attack2:
                        if(myAnimation[Attack2AnimClip.name].normalizedTime > 0.1f)
                        {
                            NextAttack = true;
                        }
                        break;
                    case FighterAttackState.Attack3:
                        if(myAnimation[Attack3AnimClip.name].normalizedTime > 0.1f)
                        {
                            NextAttack = true;
                        }
                        break;
                    case FighterAttackState.Attack4:
                        if(myAnimation[Attack4AnimClip.name].normalizedTime > 0.1f)
                        {
                            NextAttack = true;
                        }
                        break;
                }
            }
        }

        if(Input.GetMouseButtonDown(1) == true)
        {
            if(myState == FighterState.Attack)
            {
                AttackState = FighterAttackState.Attack1;
                NextAttack = false;
            }
            myState = FighterState.Skill;
        }
    }
    /// <summary>
    /// 공격 애니메이션 재생이 끝나면 호출되는 이벤트 함수
    /// <summary>
    void OnAttackAnimFinished()
    {
        if(NextAttack == true)
        {
            NextAttack = false;
            switch(AttackState)
            {
                case FighterAttackState.Attack1:
                    AttackState = FighterAttackState.Attack2;
                    break;
                case FighterAttackState.Attack2:
                    AttackState = FighterAttackState.Attack3;
                    break;
                case FighterAttackState.Attack3:
                    AttackState = FighterAttackState.Attack4;
                    break;
                case FighterAttackState.Attack4:
                    AttackState = FighterAttackState.Attack1;
                    break;
            }
        } else {
            CannotMove = false;
            myState = FighterState.Idle;
            AttackState = FighterAttackState.Attack1;
        }
    }

    void OnSkillAnimFinished()
    {
        Vector3 position = transform.position;
        position += transform.forward * 2.0f;
        Instantiate(SkillEffect, position, Quaternion.identity);
        CannotMove = false;
        myState = FighterState.Idle;
        AttackState = FighterAttackState.Attack1;
    }
    /// <summary>
    /// 애니메이션 클립 재생이 끝날때 쯤 애니메이션 이벤트 함수를 호출 시켜주도록 추가
    /// <summary>
    /// <param name="clip"></param>
    /// <param name="FuncName"></param>
    void AddAnimationEvent(AnimationClip clip, string FuncName)
    {
        AnimationEvent newEvent = new AnimationEvent();
        newEvent.functionName = FuncName;
        newEvent.time = clip.length - 0.1f;
        clip.AddEvent(newEvent);
    }
    /// <summary>
    /// 공격 애니메이션 재생
    /// <summary>
    void AttackAnimationControl()
    {
        switch(AttackState)
        {
            case FighterAttackState.Attack1:
                AnimationPlay(Attack1AnimClip);
                break;
            case FighterAttackState.Attack2:
                AnimationPlay(Attack2AnimClip);
                break;
            case FighterAttackState.Attack3:
                AnimationPlay(Attack3AnimClip);
                break;
            case FighterAttackState.Attack4:
                AnimationPlay(Attack4AnimClip);
                break;
        }
    }
    /// <summary>
    /// 중력적용
    /// <summary>
    void ApplyGravity()
    {
        //ColliderBelow가 세팅되었다면, 바닥에 붙었다면
        if((collisionFlags & CollisionFlags.CollidedBelow) != 0)
        {
            verticalSpeed = 0.0f;
        } else {
            verticalSpeed -= gravity * Time.deltaTime;
        }
    }

    void AttackComponentControl()
    {
        switch(myState)
        {
            case FighterState.Attack:
            case FighterState.Skill:
                AttackTrailRenderer.enabled = true;
                AttackCapsuleCollider.enabled = true;
                break;
            default:
                AttackTrailRenderer.enabled = false;
                AttackCapsuleCollider.enabled = false;
                break;
        }
    }
}
