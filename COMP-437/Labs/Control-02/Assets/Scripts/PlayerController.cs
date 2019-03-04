using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{

    public float speed = 6.0f;
    public float rotationSpeed = 90.0f;
    public float gravity = 20.0f;
    public float jumpSpeed = 10.0f;

    private CharacterController controller;

    private Vector3 velocity = Vector3.zero;

    // Start is called before the first frame update
    void Start()
    {
        controller = GetComponent<CharacterController>();   
    }

    // Update is called once per frame
    void Update()
    {
        float dt = Time.deltaTime;
        float horizontal = Input.GetAxis("Horizontal");
        float vertical = Input.GetAxis("Vertical");
        Move(dt, horizontal, vertical);
        Look(dt, horizontal);
    }

    private void Move(float dt, float horizontal, float vertical)
    {
        Vector3 inputVector = transform.forward * vertical;
        Vector3 movement = inputVector * speed;
        velocity.x = movement.x;
        velocity.z = movement.z;
        if(controller.isGrounded)
        {
            if(Input.GetKey(KeyCode.Space))
            {
                velocity.y = jumpSpeed;
            } else
            {
                velocity.y = 0;
            }
        }
        controller.Move(velocity * dt);
        velocity.y -= gravity * dt;
    }

    private void Look(float dt, float horizontal)
    {
        float transformationRotation = horizontal * rotationSpeed * dt;
        transform.Rotate(0, transformationRotation, 0);
    }

}
