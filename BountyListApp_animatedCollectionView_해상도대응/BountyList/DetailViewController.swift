//
//  DetailViewController.swift
//  BountyList
//
//  Created by 정성윤 on 22/07/2019.
//  Copyright © 2019 정성윤. All rights reserved.
//

import UIKit

class DetailViewController: UIViewController {
    
    @IBOutlet weak var imgView: UIImageView!
    @IBOutlet weak var nameLabel: UILabel!
    @IBOutlet weak var bountyLabel: UILabel!
    
    @IBOutlet weak var nameLabelCenterX: NSLayoutConstraint!
    @IBOutlet weak var bountyLabelCenterX: NSLayoutConstraint!
    
    var bountyInfo: BountyInfo?

    override func viewDidLoad() {
        super.viewDidLoad()
        updateUI()
        
        nameLabelCenterX.constant = view.bounds.width
        bountyLabelCenterX.constant = view.bounds.width
    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        
        nameLabelCenterX.constant = 0
//        UIView.animate(withDuration: 0.3, delay: 0, options: .curveEaseIn, animations: {self.view.layoutIfNeeded()}, completion: nil)
        UIView.animate(withDuration: 0.5, delay: 0, usingSpringWithDamping: 0.6, initialSpringVelocity: 2, options: .allowUserInteraction, animations: {self.view.layoutIfNeeded()}, completion: nil)
        bountyLabelCenterX.constant = 0
//        UIView.animate(withDuration: 0.3, delay: 0.2, options: .curveEaseIn, animations: {self.view.layoutIfNeeded()}, completion: nil)
        UIView.animate(withDuration: 0.5, delay: 0.2, usingSpringWithDamping: 0.6, initialSpringVelocity: 2, options: .allowUserInteraction, animations: {self.view.layoutIfNeeded()}, completion: nil)
        
        UIView.transition(with: imgView, duration: 0.3, options: .transitionFlipFromLeft, animations: nil, completion: nil)

        
    }
    func updateUI() {
        guard let info = bountyInfo else { return }
        imgView.image = info.image
        nameLabel.text = info.name
        bountyLabel.text = "\(info.bounty)"
    }
    @IBAction func close(_ sender: UIButton) {
        dismiss(animated: true, completion: nil)
    }


}
